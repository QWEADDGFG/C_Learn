#include "fun.h"
int main(int argc, char *argv[])
{
    // ./13_du_redirect file
    ARGS_CHECK(argc, 2);
    int fd1 = open(argv[1], O_RDWR);
    ERROR_CHECK(fd1,-1, "open");
    printf("111\n");
    close(STDOUT_FILENO);

    int fd2 = dup(fd1);
    ERROR_CHECK(fd2,-1, "dup");
    printf("fd2 = %d\n", fd2);

    printf("222\n");
    close(fd1);
    close(fd2);

    return 0;
}