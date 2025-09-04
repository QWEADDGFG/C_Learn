#include <func.h>

int main(int argc, char* argv[])
{
    // 1. 先 pipe() 
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        error(1, errno, "pipe");
    }

    // 2. 后 fork()
    char buf[1024];

    switch (fork()) {
    case -1:
        error(1, errno, "fork");
    case 0:
        // 3. 子进程关闭管道的另一端
        close(pipefd[1]);
        read(pipefd[0], buf, 1024);
        printf("Child: %s\n", buf);
        exit(0);
    default:
        // 4. 父进程关闭管道的一端
        close(pipefd[0]);
        sleep(2);
        write(pipefd[1], "Hello from parent", 18);
        exit(0);
    }

    return 0;
}

