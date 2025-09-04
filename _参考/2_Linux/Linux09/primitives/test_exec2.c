#include <func.h>

int main(int argc, char* argv[])
{
    printf("pid = %d, ppid = %d\n", getpid(), getppid());

    // 执行程序
    execl("echoall", "./echoall", "aaa", "bbb", NULL);

    error(1, errno, "execl");
    return 0;
}

