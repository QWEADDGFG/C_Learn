#include "fun.h"
int main(int argc, char *argv[])
{
    // ./6`_txt a.txt
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR|O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");

    // char str[]="1000000";
    // write(fd, str, strlen(str));

    int i = 1000000;
    write(fd, &i, sizeof(i));
    read(fd, &i, sizeof(i));
    printf("i = %d\n", i);

    close(fd);

    return 0;
}