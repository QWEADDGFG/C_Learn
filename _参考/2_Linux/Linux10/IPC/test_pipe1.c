#include <func.h>

int main(int argc, char* argv[])
{
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        error(1, errno, "pipe");
    }

    printf("pipefd[0] = %d, pipefd[1] = %d\n", pipefd[0], pipefd[1]);

    char buf[1024];
    
    write(pipefd[1], "Hello from pipe\n", 16);

    read(pipefd[0], buf, 1024);
    puts(buf);

    return 0;
}

