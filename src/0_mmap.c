#include "fun.h"
int main(int argc, char *argv[])
{
    // ./0_mmap file_name
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1,"open file failed!");

    int ret = ftruncate(fd, 5);
    ERROR_CHECK(ret, -1,"ftruncate failed!");// 在mmap之前先进行文件截断的原因

    char *addr = mmap(NULL, 5, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(addr, MAP_FAILED,"mmap failed!");

    for (int i = 0; i < 5; i++)
    {
        printf("%c", addr[i]);
    }
    printf("\n");

    addr[3] = 'a';
    munmap(addr, 5);
    close(fd);
    
    return 0;
}