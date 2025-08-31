#include "fun.h"

int main(int argc, char *argv[])
{
    // ./0_homework_fileCompare filename1 filename2
    ARGS_CHECK(argc, 3);
    int fd1 = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd1, -1, "open file1");
    int fd2 = open(argv[2], O_RDONLY);
    ERROR_CHECK(fd2, -1, "open file2");

    // char buf1[1024];
    // char buf2[1024];
    // while (1)
    // {
    //     memset(buf1, 0, sizeof(buf1));
    //     memset(buf2, 0, sizeof(buf2));
    //     ssize_t sret1 = read(fd1, buf1, sizeof(buf1));
    //     ssize_t sret2 = read(fd2, buf2, sizeof(buf2));
    //     if (sret1!= sret2 ){
    //         printf("file not equal!\n");
    //         break;
    //     }
    //     else if (memcmp(buf1, buf2, sret1)!= 0){
    //         printf("file not equal!\n");
    //         break;
    //     }
    //     else if (sret1 == 0 ){
    //         printf("file equal!\n");
    //         break;

    //     }
    // }

    char buf1[4096], buf2[4096];
    int equal = 1;
    ssize_t n1, n2;

    while ((n1 = read(fd1, buf1, sizeof(buf1))) >= 0 &&
           (n2 = read(fd2, buf2, sizeof(buf2))) >= 0)
    {
        if (n1 != n2)
        {
            equal = 0;
            break;
        }
        if (n1 == 0)
        {
            break;
        } /* 双 EOF */
        if (memcmp(buf1, buf2, n1) != 0)
        {
            equal = 0;
            break;
        }
    }

    printf("%s\n", equal ? "file equal!" : "file not equal!");
    close(fd1);
    close(fd2);
    return 0;
}
