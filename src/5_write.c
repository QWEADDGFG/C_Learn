#include "fun.h"
int main(int argc, char *argv[])
{
    // ./5_write filename
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");
    char *str = "Hello, world!\n";
    int len = strlen(str);
    int sret = write(fd, str, len);
    ERROR_CHECK(sret, -1, "write");
    printf("write %d bytes to %s\n", sret, argv[1]);
    close(fd);
    return 0;
}