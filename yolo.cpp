#include <dirent.h>
#include <opencv2/opencv.hpp>
#include "AclLiteUtils.h"
#include "AclLiteImageProc.h"
#include "AclLiteResource.h"
#include "AclLiteError.h"
#include "AclLiteModel.h"
#include "label.h"
#include <chrono>
#include <fstream>
#include <sys/stat.h> 

using namespace std;
using namespace cv;

// 返回值枚举，便于上下文表达成功/失败
typedef enum Result
{
    SUCCESS = 0,
    FAILED = 1
} Result;

// 边界框结构体，保存检测框坐标、置信度、类别索引等
typedef struct BoundBox
{
    float x;            // 中心点或框描述的 x（代码里为中心点）
    float y;            // 中心点或框描述的 y
    float width;        // 宽
    float height;       // 高
    float score;        // 置信度
    size_t classIndex;  // 类别索引
    size_t index;       // 在模型输出中的索引（可用于追溯）
} BoundBox;

// 按分数降序排序（NMS 前需要先按置信度从大到小排序）
bool sortScore(BoundBox box1, BoundBox box2)
{
    return box1.score > box2.score;
}

// SampleYOLOV8 类封装了模型初始化、输入处理、推理、结果处理等
class SampleYOLOV8
{
public:
    SampleYOLOV8(const char *modelPath, const int32_t modelWidth, const int32_t modelHeight);
    Result InitResource(); // 初始化 ACL、模型、图像处理等资源
    Result ProcessInput(string testImgPath); // 读取并预处理图片（缩放到模型输入）
    Result Inference(std::vector<InferenceOutput> &inferOutputs); // 执行推理
    Result GetResult(std::vector<InferenceOutput> &inferOutputs, 
                     string imagePath, 
                     const string& outputImgDir,
                     const string& outputTxtDir); // 后处理并保存结果
    ~SampleYOLOV8();

private:
    void ReleaseResource(); // 释放资源
    AclLiteResource aclResource_; // ACL 资源封装
    AclLiteImageProc imageProcess_; // 图像处理封装（DVPP 等）
    AclLiteModel model_; // 模型封装
    aclrtRunMode runMode_; // 运行模式（设备/宿主）
    ImageData resizedImage_; // 预处理后传给模型的数据
    const char *modelPath_;
    int32_t modelWidth_; // 模型输入宽
    int32_t modelHeight_; // 模型输入高
};

// 构造函数
SampleYOLOV8::SampleYOLOV8(const char *modelPath, const int32_t modelWidth, const int32_t modelHeight)
    : modelPath_(modelPath), modelWidth_(modelWidth), modelHeight_(modelHeight)
{
}

// 析构函数负责释放资源
SampleYOLOV8::~SampleYOLOV8()
{
    ReleaseResource();
}

// 初始化资源：ACL、运行模式、图像处理、模型
Result SampleYOLOV8::InitResource()
{
    AclLiteError ret = aclResource_.Init();
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("resource init failed, errorCode is %d", ret);
        return FAILED;
    }

    ret = aclrtGetRunMode(&runMode_);
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("get runMode failed, errorCode is %d", ret);
        return FAILED;
    }

    ret = imageProcess_.Init();
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("imageProcess init failed, errorCode is %d", ret);
        return FAILED;
    }

    ret = model_.Init(modelPath_);
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("model init failed, errorCode is %d", ret);
        return FAILED;
    }
    return SUCCESS;
}

// ProcessInput: 读取 JPEG 文件 -> 复制到 device -> 解码为 YUV -> resize 到模型输入
Result SampleYOLOV8::ProcessInput(string testImgPath)
{
    ImageData image;
    AclLiteError ret = ReadJpeg(image, testImgPath);
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("ReadJpeg failed, errorCode is %d", ret);
        return FAILED;
    }

    // 将原始 JPEG 数据拷贝到设备上（DVPP 等）
    ImageData imageDevice;
    ret = CopyImageToDevice(imageDevice, image, runMode_, MEMORY_DVPP);
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("CopyImageToDevice failed, errorCode is %d", ret);
        return FAILED;
    }

    // 使用 DVPP/JPEG 解码到 YUV 格式
    ImageData yuvImage;
    ret = imageProcess_.JpegD(yuvImage, imageDevice);
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("Convert jpeg to yuv failed, errorCode is %d", ret);
        return FAILED;
    }

    // 将 YUV 图像 resize 到模型期望的输入大小（并存放到 resizedImage_）
    ret = imageProcess_.Resize(resizedImage_, yuvImage, modelWidth_, modelHeight_);
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("Resize image failed, errorCode is %d", ret);
        return FAILED;
    }
    return SUCCESS;
}

// Inference: 将预处理好的数据设置为模型输入并执行推理，输出在 inferOutputs 中
Result SampleYOLOV8::Inference(std::vector<InferenceOutput> &inferOutputs)
{
    AclLiteError ret = model_.CreateInput(static_cast<void *>(resizedImage_.data.get()), resizedImage_.size);
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("CreateInput failed, errorCode is %d", ret);
        return FAILED;
    }

    // 执行模型
    ret = model_.Execute(inferOutputs);
    if (ret != ACL_SUCCESS)
    {
        ACLLITE_LOG_ERROR("execute model failed, errorCode is %d", ret);
        return FAILED;
    }

    return SUCCESS;
}

// GetResult: 后处理推理输出 -> 过滤 -> NMS -> 写入 TXT -> 绘制并保存图片
Result SampleYOLOV8::GetResult(std::vector<InferenceOutput> &inferOutputs,
                               string imagePath, 
                               const string& outputImgDir,
                               const string& outputTxtDir)
{
    // 假设模型只有一个输出 buffer，id 为 0（注意：具体模型可能有多个输出，此处根据原始示例处理）
    uint32_t outputDataBufId = 0;
    float *classBuff = static_cast<float *>(inferOutputs[outputDataBufId].data.get());

    // 置信度阈值（低于该值的预测被丢弃）
    float confidenceThreshold = 0.001;

    // 类别数（示例代码中使用 1，实际请根据模型类别数修改）
    size_t classNum = 1;

    // 偏移量：输出中前 4 个元素为 bbox(x,y,w,h)，然后是各类概率
    size_t offset = 4;

    // 模型输出的 box 数量（示例中使用 21760，需根据具体模型确认）
    // 注：原作者也给过 5376 等不同值，取决于模型的特征层组合
    size_t modelOutputBoxNum = 21760; 

    // 读取原始图片，用于绘制检测框与转换坐标
    cv::Mat srcImage = cv::imread(imagePath);
    int srcWidth = srcImage.cols;
    int srcHeight = srcImage.rows;

    // 从 imagePath 中提取文件名（不含扩展名），用于输出文件命名
    size_t lastSlash = imagePath.find_last_of("/");
    size_t lastDot = imagePath.find_last_of(".");
    string fileName = imagePath.substr(lastSlash + 1, lastDot - lastSlash - 1);
    
    // 构造输出路径（图片与标签）
    string outputImagePath = outputImgDir + "/" + fileName + ".jpg";
    string outputTxtPath = outputTxtDir + "/" + fileName + ".txt";

    // 用于保存筛选后的候选框
    vector<BoundBox> boxes;
    // 下标映射：根据输出数据 layout，0->x, 1->y, 2->w, 3->h
    size_t yIndex = 1;
    size_t widthIndex = 2;
    size_t heightIndex = 3;
    
    // 解析模型输出：
    // 对于输出 layout 为 (1, C, N) 且 C = 4 + classNum（例如 (1, 5, N) -> 4 bboxes + 1 class prob）
    // classBuff[(offset + j) * modelOutputBoxNum + i]  表示第 i 个 box 的第 j 类概率
    for (size_t i = 0; i < modelOutputBoxNum; ++i)
    {
        float maxValue = 0;
        size_t maxIndex = 0;
        // 找到当前 box 的最大类别概率
        for (size_t j = 0; j < classNum; ++j)
        {
            float value = classBuff[(offset + j) * modelOutputBoxNum + i];
            if (value > maxValue)
            {
                maxIndex = j;
                maxValue = value;
            }
        }

        // 置信度过滤
        if (maxValue > confidenceThreshold)
        {
            BoundBox box;
            // 将模型输出的 bbox（通常为归一化形式或相对模型尺寸的数值）转换为原图坐标尺度
            box.x = classBuff[i] * srcWidth / modelWidth_;
            box.y = classBuff[yIndex * modelOutputBoxNum + i] * srcHeight / modelHeight_;
            box.width = classBuff[widthIndex * modelOutputBoxNum + i] * srcWidth / modelWidth_;
            box.height = classBuff[heightIndex * modelOutputBoxNum + i] * srcHeight / modelHeight_;
            box.score = maxValue;
            box.classIndex = maxIndex;
            box.index = i;
            if (maxIndex < classNum)
            {
                boxes.push_back(box);
            }
        }
    }

    // 另外一种常见的输出格式注释（示例中被注释掉的另一种解析方式）
    /*
    // 模型输出(1,5376,6) 的解析示例
    for (size_t i = 0; i < modelOutputBoxNum; ++i)
    {
        float x = classBuff[i * 6 + 0] * srcWidth  / modelWidth_;
        float y = classBuff[i * 6 + 1] * srcHeight / modelHeight_;
        float w = classBuff[i * 6 + 2] * srcWidth  / modelWidth_;
        float h = classBuff[i * 6 + 3] * srcHeight / modelHeight_;
        float conf = classBuff[i * 6 + 4];
        float cls  = classBuff[i * 6 + 5];
        if (conf > confidenceThreshold)
        {
            BoundBox box;
            box.x = x;
            box.y = y;
            box.width = w;
            box.height = h;
            box.score = conf;
            box.classIndex = static_cast<size_t>(cls);
            box.index = i;
            boxes.push_back(box);
        }
    }
    */

    ACLLITE_LOG_INFO("filter boxes by confidence threshold > %f success, boxes size is %ld", confidenceThreshold, boxes.size());

    // NMS（非极大抑制）
    vector<BoundBox> result;
    result.clear();
    float NMSThreshold = 0.45; // NMS IOU 阈值
    // 为了避免不同类别的框互相抑制，示例中通过将 x,y 平移 maxLength * classIndex 来避开不同类间的重叠判断
    int32_t maxLength = modelWidth_ > modelHeight_ ? modelWidth_ : modelHeight_;
    std::sort(boxes.begin(), boxes.end(), sortScore); // 按置信度降序排列

    // 逐个挑选置信度最高的框，剔除与其 IoU 超过阈值的框
    while (boxes.size() != 0)
    {
        size_t index = 1;
        result.push_back(boxes[0]); // 选取当前置信度最高者
        while (boxes.size() > index)
        {
            BoundBox boxMax;
            BoundBox boxCompare;
            // 将 boxMax 平移（按类别）以避免不同类别之间相互比较
            boxMax.score = boxes[0].score;
            boxMax.classIndex = boxes[0].classIndex;
            boxMax.index = boxes[0].index;
            boxMax.x = boxes[0].x + maxLength * boxes[0].classIndex;
            boxMax.y = boxes[0].y + maxLength * boxes[0].classIndex;
            boxMax.width = boxes[0].width;
            boxMax.height = boxes[0].height;

            boxCompare.score = boxes[index].score;
            boxCompare.classIndex = boxes[index].classIndex;
            boxCompare.index = boxes[index].index;
            boxCompare.x = boxes[index].x + boxes[index].classIndex * maxLength;
            boxCompare.y = boxes[index].y + boxes[index].classIndex * maxLength;
            boxCompare.width = boxes[index].width;
            boxCompare.height = boxes[index].height;

            // 计算重叠部分
            float xLeft = max(boxMax.x, boxCompare.x);
            float yTop = max(boxMax.y, boxCompare.y);
            float xRight = min(boxMax.x + boxMax.width, boxCompare.x + boxCompare.width);
            float yBottom = min(boxMax.y + boxMax.height, boxCompare.y + boxCompare.height);
            float width = max(0.0f, xRight - xLeft);
            float hight = max(0.0f, yBottom - yTop);
            float area = width * hight;
            float iou = area / (boxMax.width * boxMax.height + boxCompare.width * boxCompare.height - area);

            // 若 IOU 超过阈值，则删除较小置信度的 box（即 boxes[index]）
            if (iou > NMSThreshold)
            {
                boxes.erase(boxes.begin() + index);
                continue; // 不增加 index，因为当前 index 被删除，需要再次检查新元素
            }
            ++index;
        }
        // 删除当前最高分框（已加入 result）
        boxes.erase(boxes.begin());
    }

    ACLLITE_LOG_INFO("filter boxes by NMS threshold > %f success, result size is %ld", NMSThreshold, result.size());
    
    // ============ 将检测结果写入 TXT（每行：class x_center y_center width height score，坐标为相对原图归一化值） ============
    ofstream txtFile(outputTxtPath);
    if (!txtFile.is_open()) {
        ACLLITE_LOG_ERROR("Cannot open output TXT file: %s", outputTxtPath.c_str());
        return FAILED;
    }
    
    for (size_t i = 0; i < result.size(); ++i) {
        // 代码中 result[i].x, .y 表示中心点（按实现意图）
        float x_center_norm = result[i].x / srcWidth;
        float y_center_norm = result[i].y / srcHeight;
        float width_norm = result[i].width / srcWidth;
        float height_norm = result[i].height / srcHeight;
        
        // 写入格式（常见格式类似 YOLO txt，第一列为类别）
        txtFile << result[i].classIndex << " "
                << x_center_norm << " "
                << y_center_norm << " "
                << width_norm << " "
                << height_norm << " "
                << result[i].score << endl;
    }
    txtFile.close();
    // =================================================

    // 绘制检测结果到原始图片并保存
    const double fountScale = 0.5;
    const uint32_t lineSolid = 2;
    const uint32_t labelOffset = 11;
    const cv::Scalar fountColor(0, 0, 255); // 文本颜色：红（BGR）
    const vector<cv::Scalar> colors{
        cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0),
        cv::Scalar(0, 0, 255)}; // 框的颜色循环

    int half = 2; // 用于把中心点/尺寸转为左上、右下
    for (size_t i = 0; i < result.size(); ++i)
    {
        cv::Point leftUpPoint, rightBottomPoint;
        // result[i].x, y 存储的是中心点坐标，此处计算左上与右下
        leftUpPoint.x = static_cast<int>(result[i].x - result[i].width / half);
        leftUpPoint.y = static_cast<int>(result[i].y - result[i].height / half);
        rightBottomPoint.x = static_cast<int>(result[i].x + result[i].width / half);
        rightBottomPoint.y = static_cast<int>(result[i].y + result[i].height / half);

        // 绘制矩形框
        cv::rectangle(srcImage, leftUpPoint, rightBottomPoint, colors[i % colors.size()], lineSolid);

        // 获取类别名称（来自 label.h）
        string className = label[result[i].classIndex];
        string markString = to_string(result[i].score) + ":" + className;

        ACLLITE_LOG_INFO("object detect [%s] success", markString.c_str());

        // 在框左上处写类别与置信度文本
        cv::putText(srcImage, markString, cv::Point(leftUpPoint.x, leftUpPoint.y + labelOffset),
                    cv::FONT_HERSHEY_COMPLEX, fountScale, fountColor);
    }
    
    // 保存输出图片到指定目录
    cv::imwrite(outputImagePath, srcImage);
    
    return SUCCESS;
}

// 释放资源：销毁模型、图像处理、ACL 资源
void SampleYOLOV8::ReleaseResource()
{
    model_.DestroyResource();
    imageProcess_.DestroyResource();
    aclResource_.Release();
}

// 创建目录（若不存在则创建）。仅对简单场景有效（Linux 下）
void createDirectory(const string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        mkdir(path.c_str(), 0777); // 创建目录，权限 0777（根据需要可改）
        ACLLITE_LOG_INFO("Created directory: %s", path.c_str());
    } else if (info.st_mode & S_IFDIR) {
        ACLLITE_LOG_INFO("Directory exists: %s", path.c_str());
    } else {
        ACLLITE_LOG_ERROR("Path exists but is not a directory: %s", path.c_str());
    }
}

int main()
{
    // 模型路径（根据注释选择适合的模型）
    // const char *modelPath = "../model/best_nextvit200.om";//输出(1,5376,6)
    // const char *modelPath = "../model/best0818.om";//输出(1,5,5376)
    // const char *modelPath = "../model/bestv8s.om";//输出(1,5,5376)
    // const char *modelPath = "../model/best11s.om";//输出(1,5,5376)
    // const char *modelPath = "../model/best11sp2.om";//输出(1,5,21760)
    // const char *modelPath = "../model/bestv8sp2.om";//输出(1,5,21760)
    // const char *modelPath = "../model/bestgp2.om";//输出(1,5,21760)
    const char *modelPath = "../model/bestca.om";//输出(1,5,21760)

    // 待推理图片目录
    const string imagePath = "../DATASETS/IRSTD_1K/imgs_test_jpg";

    // 模型输入尺寸（需与模型实际输入尺寸一致）
    const int32_t modelWidth = 512;
    const int32_t modelHeight = 512;
    
    // 输出目录（图片和标签）
    const string outputImgDir = "../output/images";
    const string outputTxtDir = "../output/labels";
    
    // 创建输出目录（若不存在）
    createDirectory("../output");
    createDirectory(outputImgDir);
    createDirectory(outputTxtDir);

    // 打开图片目录，收集所有图片路径
    DIR *dir = opendir(imagePath.c_str());
    if (dir == nullptr)
    {
        ACLLITE_LOG_ERROR("file folder does no exist, please create folder %s", imagePath.c_str());
        return FAILED;
    }
    vector<string> allPath;
    struct dirent *entry;
    while ((entry = readdir(dir)) != nullptr)
    {
        // 忽略 . 和 .. 及 .keep 等隐藏或不需要的文件
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".keep") == 0)
        {
            continue;
        }
        else
        {
            string name = entry->d_name;
            string imgDir = imagePath + "/" + name;
            allPath.push_back(imgDir);
        }
    }
    closedir(dir);

    if (allPath.size() == 0)
    {
        ACLLITE_LOG_ERROR("the directory is empty, please download image to %s", imagePath.c_str());
        return FAILED;
    }

    // 创建 SampleYOLOV8 实例并初始化资源
    string fileName;
    SampleYOLOV8 sampleYOLO(modelPath, modelWidth, modelHeight);
    Result ret = sampleYOLO.InitResource();
    if (ret == FAILED)
    {
        ACLLITE_LOG_ERROR("InitResource failed, errorCode is %d", ret);
        return FAILED;
    }

    // 记录总时间和图片数，用于计算平均 FPS（剔除首张 warmup）
    double total_time = 0.0;
    size_t total_images = 0;

    // 遍历所有图片进行推理
    for (size_t i = 0; i < allPath.size(); i++)
    {
        std::vector<InferenceOutput> inferOutputs;
        fileName = allPath.at(i).c_str();
        std::chrono::time_point<std::chrono::steady_clock> start = std::chrono::steady_clock::now();

        // 1) 预处理
        ret = sampleYOLO.ProcessInput(fileName);
        if (ret == FAILED)
        {
            ACLLITE_LOG_ERROR("ProcessInput image failed, errorCode is %d", ret);
            return FAILED;
        }
        
        // 2) 推理
        ret = sampleYOLO.Inference(inferOutputs);
        if (ret == FAILED)
        {
            ACLLITE_LOG_ERROR("Inference failed, errorCode is %d", ret);
            return FAILED;
        }

        // 3) 后处理（并保存图片与 TXT）
        ret = sampleYOLO.GetResult(inferOutputs, fileName, outputImgDir, outputTxtDir);
        if (ret == FAILED)
        {
            ACLLITE_LOG_ERROR("GetResult failed, errorCode is %d", ret);
            return FAILED;
        }

        std::chrono::time_point<std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        if (i == 0) {
            // 首张图片作为 warmup，通常耗时较久，不计入平均 FPS
            ACLLITE_LOG_INFO("Warmup (image %zu) elapsed time: %f s , fps: %f", i, elapsed.count(), 1.0 / elapsed.count());
        } else {
            // 后续图片计入平均统计
            total_time += elapsed.count();
            total_images++;
            ACLLITE_LOG_INFO("Image %zu elapsed time: %f s , fps: %f", i, elapsed.count(), 1.0 / elapsed.count());
        }
    }

    // 计算并打印平均 FPS（剔除首张 warmup）
    if (total_images > 0) {
        double avg_fps = total_images / total_time;
        ACLLITE_LOG_INFO("Processed %zu images (excluding warmup), average FPS: %f", total_images, avg_fps);
    }

    return SUCCESS;
}
