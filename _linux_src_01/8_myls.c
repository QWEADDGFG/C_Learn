#include "fun.h"

/**
* @brief 主函数，用于列出指定目录下的文件信息，并在找到特定目录后重新定位到该目录并再次读取
*
* @param argc 命令行参数个数
* @param argv 命令行参数数组
*
* @return 0 表示程序正常退出
*/
int main(int argc, char *argv[])
{
    // ./8_myls dir1
    ARGS_CHECK(argc, 2);

    DIR *dirp = opendir(argv[1]);
    ERROR_CHECK(dirp, NULL, "opendir");

    struct dirent *pdirent;
    long loc;
    while( (pdirent = readdir(dirp)) != NULL){
        printf("inode_num = %ld, reclen = %d, type = %d, name = %s\n",
               pdirent->d_ino, pdirent->d_reclen,
               pdirent->d_type, pdirent->d_name);
        if(strcmp("dir2",pdirent->d_name) == 0){
            loc = telldir(dirp);
        }
    }   

    seekdir(dirp, loc);
    // rewinddir(dirp);
    pdirent = readdir(dirp);

    printf("---------------------------\n");
    printf("inode_num = %ld, reclen = %d, type = %d, name = %s\n",
           pdirent->d_ino, pdirent->d_reclen,
           pdirent->d_type, pdirent->d_name);

    closedir(dirp);
    return 0;
}

