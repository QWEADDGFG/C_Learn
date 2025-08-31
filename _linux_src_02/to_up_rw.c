#include "fun.h"
int main(int argc, char *argv[])
{
    // ./to_up_rw file_name
    // 将文件中所有小写字母转换为大写字母 -- lseek、read、write、close
    // lseek之后，需要lseek回到起点，再mmap
    ARGS_CHECK(argc, 2);
    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    char buf;
    while (1)
    {
        ssize_t sret = read(fd, &buf, sizeof(buf));
        if (sret <= 0)
            break;
        if (buf >= 'a' && buf <= 'z')
        {
            buf = buf - 'a' + 'A';
            lseek(fd, -1, SEEK_CUR);
            write(fd, &buf, sizeof(buf));
        }
    }

    return 0;
}