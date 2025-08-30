#include "fun.h"
int main(int argc, char *argv[])
{
    // ./9_ftruncate file
    ARGS_CHECK(argc, 2);
    int fd =open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");
    int ret = ftruncate(fd, 10);
    ERROR_CHECK(ret, -1, "ftruncate");
    close(fd);
    return 0;
}