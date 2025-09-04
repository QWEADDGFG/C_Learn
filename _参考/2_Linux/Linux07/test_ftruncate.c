#include <func.h>

int main(int argc, char* argv[])
{
    // ./test_ftruncate file length 
    if (argc != 3) {
        error(1, 0, "Usage: %s file length", argv[0]);
    }

    off_t length;
    sscanf(argv[2], "%ld", &length);
    
    int fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        error(1, errno, "open %s", argv[1]);
    }

    if (ftruncate(fd, length) == -1) {
        error(1, errno, "fruncate %d", fd);
    }

    close(fd);

    return 0;
}

