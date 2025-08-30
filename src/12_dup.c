#include "fun.h"
int main(int argc, char *argv[])
{
    // ./12_dup file1
    ARGS_CHECK(argc, 2);
    int oldfd = open(argv[1], O_RDWR);
    ERROR_CHECK(oldfd, -1, "open");
    printf("oldfd = %d\n", oldfd);
    int newfd = dup(oldfd);
    ERROR_CHECK(newfd, -1, "dup");
    printf("newfd = %d\n", newfd);

    write(newfd, "hello", 5);
    write(oldfd, "world", 5);
    close(oldfd);
    close(newfd);
    return 0;
}