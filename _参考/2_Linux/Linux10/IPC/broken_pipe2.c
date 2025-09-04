#include <func.h>

int main(int argc, char* argv[])
{
    int fd = open("pipe1", O_RDONLY);
    if (fd == -1) {
        error(1, errno, "open pipe1");
    }
    printf("Established\n");

    close(fd);
    return 0;
}

