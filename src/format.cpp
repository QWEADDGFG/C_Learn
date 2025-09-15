#include "cplusplus.h"
using namespace std;
using namespace std::chrono;
int main()
{
    // 基本格式化
    cout << fmt::format("Hello, {}!", "world") << endl;
    fmt::print("Hello, {}!\n", "world"); // 输出: Hello, world!

    // 带位置的参数
    cout << fmt::format("{1}, {0}!", "Hello", "world") << endl;
    fmt::print("{1}, {0}!\n", "Hello", "world"); // 输出: world, Hello!
    fmt::print("--------------------------------------\n");

    int num = 42;
    double pi = 3.1415926535;

    // // 整数格式化
    // cout << fmt::format("十进制: {}\n", num);     // 42
    // cout << fmt::format("十六进制: {:x}\n", num); // 2a
    // cout << fmt::format("八进制: {:o}\n", num);   // 52
    // cout << fmt::format("二进制: {:b}\n", num);   // 101010

    // // 浮点数格式化
    // cout << fmt::format("默认: {}\n", pi);            // 3.1415926535
    // cout << fmt::format("保留2位小数: {:.2f}\n", pi); // 3.14
    // cout << fmt::format("科学计数法: {:.2e}\n", pi);  // 3.14e+00
    // cout << fmt::format("固定宽度: {:10.3f}\n", pi);  // "     3.142"

    // 整数格式化（直接打印）
    fmt::print("{}\n", num);   // 十进制: 42
    fmt::print("{:x}\n", num); // 十六进制: 2a
    fmt::print("{:o}\n", num); // 八进制: 52
    fmt::print("{:b}\n", num); // 二进制: 101010

    // 浮点数格式化
    fmt::print("{}\n", pi);      // 默认: 3.1415926535
    fmt::print("{:.2f}\n", pi);  // 保留2位小数: 3.14
    fmt::print("{:.2e}\n", pi);  // 科学计数法: 3.14e+00
    fmt::print("{:6.3f}\n", pi); // 固定宽度: " 3.142"
    fmt::print("--------------------------------------\n");

    std::string str = "hello";

    fmt::print("{}\n", str);     // 原始: hello
    fmt::print("{:^10}\n", str); // 居中:   "  hello   "
    fmt::print("{:<10}\n", str); // 左对齐: "hello     "
    fmt::print("{:>10}\n", str); // 右对齐: "     hello"
    fmt::print("{:.3}\n", str);  // 截断:  hel

    fmt::print("--------------------------------------\n");
    auto now = system_clock::now();

    fmt::print("当前时间: {:%Y-%m-%d %H:%M:%S}\n", now);
    fmt::print("日期: {:%F}\n", now); // 2023-12-07
    fmt::print("时间: {:%T}\n", now); // 14:30:25

    fmt::print("--------------------------------------\n");
    string s, line;
    cin >> s;
    fmt::print("输入1: {}\n", s); // GuoPeng

    // 清除输入缓冲区中的剩余内容（包括换行符）
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.ignore();

    fmt::print("--------------------------------------\n");
    getline(cin, line);
    fmt::print("输入2: {}\n", line); // nihao
    /*
    --------------------------------------
    123
    输入1: 123
    --------------------------------------
    输入2:

    问题描述：
    并没有机会让用户输入输入2

    产生原因：
    这个问题是由于 cin >> s 和 getline(cin, line) 混合使用时产生的输入缓冲区问题。
    当你输入 123 并按下回车时，实际上输入的是："123\n"
    cin >> s 读取了 "123"，但换行符 \n 仍然留在输入缓冲区中
    getline(cin, line) 遇到换行符就立即返回，读取到一个空字符串

    解决办法：
    // 清除输入缓冲区中的剩余内容（包括换行符）
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    --------------------------------------
    ！！！ @@@@     qwe 你好
    输入1: ！！！
    --------------------------------------
    ！！！ @@@@   你好
    输入2: ！！！ @@@@   你好

    cin会忽略空格及其后面的键盘输入，所以输入1是"！！！"，
    std::getline 会读取输入流中的一整行，包括空格，直到遇到换行符或指定的分隔符。所以输入2是"！！！ @@@@   你好"
    */

    return 0;
}