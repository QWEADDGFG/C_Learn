#include "fun.h"
int main(int argc, char *argv[])
{
    // ./2_fread.c file1
    ARGS_CHECK(argc, 2);
    FILE *fp = fopen(argv[1], "r+");
    ERROR_CHECK(fp, NULL, "guopeng");

    char buf[1024] = {0};
    /*fread会尝试从文件中读取sizeof(buf)字节的数据到buf中。
    如果文件大小小于1024字节，fread会读取到文件末尾并停止；
    如果文件大小大于或等于1024字节，fread会读取前1024字节。*/
    fread(buf, 1, sizeof(buf), fp);
    printf("buf = %s\n", buf);
    fclose(fp);
    return 0;
}