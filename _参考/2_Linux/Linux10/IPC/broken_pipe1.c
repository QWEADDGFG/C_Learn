#include <func.h>

int main(int argc, char* argv[])
{
    int fd = open("pipe1", O_WRONLY);
    if (fd == -1) {
        error(1, errno, "open pipe1");
    }
    printf("Established\n");

    sleep(5);

    write(fd, "Hello world\n", 11);

    printf("END\n");
    return 0;
}

