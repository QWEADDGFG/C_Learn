#include <func.h>
#include <sys/uio.h>

int main()
{
    char buff1[5] = {0};
    char buff2[6] = {0};

    struct iovec iovs[2];
    iovs[0].iov_base = buff1;
    iovs[0].iov_len = 5;

    iovs[1].iov_base = buff2;
    iovs[1].iov_len = 5;

    int fd = open("file.txt", O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    int ret = readv(fd, iovs, 2);
    printf("read %d bytes.\n", ret);
    printf("buff1: %s\n", buff1);
    printf("buff2: %s\n", buff2);

    return 0;
}

