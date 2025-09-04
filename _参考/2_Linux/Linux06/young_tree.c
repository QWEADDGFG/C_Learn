// young_tree.c
#include <func.h>

void dfs_print(const char* path, int width);	/* width: 缩进的空格数目 */

int directories = 0, files = 0;

int main(int argc, char *argv[])
{
    // ./young_tree dir
    if (argc != 2) {
        error(1, 0, "Usage: %s dir", argv[0]);
    }

    puts(argv[1]);		// 遍历根结点

    dfs_print(argv[1], 4);	// 递归打印每一个子树

    printf("\n%d directories, %d files\n", directories, files);		// 最后打印统计信息
    return 0;
}

void dfs_print(const char* path, int width) {
    // 打开目录流
    DIR* stream = opendir(path);
    if (!stream) {
        error(1, errno, "opender %s", path);
    }

    // 遍历每一目录项
    errno = 0;
    struct dirent* pdirent;
    while ((pdirent = readdir(stream)) != NULL) {
        char* filename = pdirent->d_name;
        // 忽略 . 和 ..
        // if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
        //    continue;
        // }

        // 忽略隐藏文件
        if (filename[0] == '.') {
            continue;
        }

        // 打印这个目录项的名字
        for(int i = 0; i < width; i++) {
            putchar(' ');
        }
        puts(filename);
        
        if (pdirent->d_type == DT_DIR) {
            directories++;
            // 拼接路径
            char subpath[128];
            sprintf(subpath, "%s/%s", path, filename);
            dfs_print(subpath, width + 4);
        } else {
            files++;
        }
    } // pdirent == NULL 

    closedir(stream);
    
    if (errno) {
        error(1, errno, "readdir");
    }
}
