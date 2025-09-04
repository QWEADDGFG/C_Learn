#include <func.h>

int my_system(const char* cmd) {
    pid_t pid = fork();
    switch(pid) {
    case -1:
        error(1, errno, "fork");
    case 0:
        // 子进程执行新的可执行程序
        execlp("sh", "sh", "-c", cmd, NULL);
        error(1, errno, "exelp");
    default:
        // 父进程
        waitpid(pid, NULL, 0);
    }
}

int main(int argc, char* argv[])
{
    // system("top");
    my_system("top");
    return 0;
}

