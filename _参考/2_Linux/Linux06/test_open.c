#include <func.h>

int main(int argc, char* argv[])
{
    // ./test_open file 
    if (argc != 2) {
        error(1, 0, "Usage: %s file", argv[0]);
    }

    // int fd = open(argv[1], O_RDWR);
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        error(1, errno, "open %s", argv[1]);
    }

    // 获取了文件描述符
    printf("fd = %d\n", fd);

    return 0;
}

