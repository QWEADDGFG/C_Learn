#include "fun.h"
int main(int argc, char *argv[])
{
    // ./7_mycp src_file dst_file
    // 通过组合read与write函数实现文件拷贝
    ARGS_CHECK(argc, 3);
    int src_fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(src_fd, -1, "open_read");
    int dst_fd = open(argv[2], O_WRONLY | O_CREAT, 0666);
    ERROR_CHECK(dst_fd, -1, "open_write");

    char buf[1024] = {0}; // 使用char数组的原因是方便控制缓冲区大小
    ssize_t sret = read(src_fd, buf, sizeof(buf));
    write(dst_fd, buf, sret);//使用sret的原因是避免读到文件末尾时，write函数一直阻塞

    close(src_fd);
    close(dst_fd);
    return 0;
}