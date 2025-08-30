#include "fun.h"
int main(int argc, char *argv[])
{
    // ./to_up file_name
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1,"open file failed!");

    int ret = ftruncate(fd, 12);
    ERROR_CHECK(ret, -1,"ftruncate failed!");// 在mmap之前先进行文件截断的原因

    char *addr = mmap(NULL, 12, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(addr, MAP_FAILED,"mmap failed!");

    for (int i = 0; i < 12; i++)
    {
        if(addr[i] >= 'a' && addr[i] <= 'z')
        {
            addr[i] = addr[i] - 32;
        }
        printf("%c", addr[i]);
    }
    printf("\n");
    
    munmap(addr, 12);
    close(fd);
    
    return 0;
}