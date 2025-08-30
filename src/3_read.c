#include "fun.h"
int main(int argc, char *argv[])
{
    // ./3_read filename
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd, -1, "open");
    char buf[6] = {0};

    ssize_t sret = read(fd, buf, sizeof(buf));
    ERROR_CHECK(sret, -1, "read");
    printf("sret = %ld, buf = %s\n", sret, buf);

    memset(buf, 0, sizeof(buf)); // read之前清空缓冲区
    sret = read(fd, buf, sizeof(buf));
    ERROR_CHECK(sret, -1, "read");
    printf("sret = %ld, buf = %s\n", sret, buf);

    memset(buf, 0, sizeof(buf)); // read之前清空缓冲区
    sret = read(fd, buf, sizeof(buf));
    ERROR_CHECK(sret, -1, "read");
    printf("sret = %ld, buf = %s\n", sret, buf);
    close(fd);
    return 0;
}