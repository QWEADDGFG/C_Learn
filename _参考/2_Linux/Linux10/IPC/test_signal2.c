#include <func.h>

int main(int argc, char* argv[])
{
    printf("pid = %d\n", getpid());

    // 忽略 SIGINT 信号
    sighandler_t oldhandler = signal(SIGINT, SIG_IGN);
    if (oldhandler == SIG_ERR) {
        error(1, errno, "signal SIGINT");
    }

    sleep(10);

    printf("Wake up\n");
    
    signal(SIGINT, SIG_DFL);

    for(;;) {

    }
    return 0;
}

