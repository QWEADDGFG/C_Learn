#include <func.h>

int main(int argc, char* argv[])
{
    printf("BEGIN:\n"); // stdout是行缓冲

    pid_t pid = fork();
    switch (pid) {
    case -1:
        error(1, errno, "fork");
    case 0:
        // 子进程
        printf("I am a baby\n");
        exit(0);
    default:
        // 父进程
        sleep(2);
        printf("Who's your daddy?\n");
        exit(0);
    }
    return 0;
}

