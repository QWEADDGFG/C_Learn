#include <func.h>
#include <sys/uio.h>

int main()
{
    char buff1[64] = "hello";
    char buff2[64] = "world";

    struct iovec iovs[2];
    iovs[0].iov_base = buff1;
    iovs[0].iov_len = strlen(buff1);

    iovs[1].iov_base = buff2;
    iovs[1].iov_len = strlen(buff2);

    int fd = open("file.txt", O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    //聚集写的操作,
    //writev是一个系统调用，它可以提高程序的执行效率
    //(如果不使用writev，那就需要多次write操作，
    //才能完成数据的写入)
    int ret = writev(fd, iovs, 2);
    printf("write %d bytes.\n", ret);

    return 0;
}

