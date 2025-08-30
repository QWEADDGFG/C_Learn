#include "fun.h"
int main(int argc, char *argv[])
{
    // ./11_redirect file1
    // 该程序通过重定向，将标准输出重定向到文件，并将标准输出关闭，从而实现将程序的输出写入到文件。
    ARGS_CHECK(argc, 2);
    printf("you can see me\n");
    close(STDOUT_FILENO);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    printf("fd = %d\n", fd);
    printf("you can not see me\n");
    return 0;
}