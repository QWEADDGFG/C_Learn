#include <func.h>

void handler(int signo) {
    switch (signo) {
    case SIGKILL:
        printf("Caught SIGKILL\n");
        break;
    case SIGSTOP:
        printf("Caught SIGSTOP\n");
        break;
    }
}

int main(int argc, char* argv[])
{
    printf("pid = %d\n", getpid());

    sighandler_t oldhandler = signal(SIGKILL, handler);
    if (oldhandler == SIG_ERR) {
        error(0, errno, "signal SIGKILL");
    }


    oldhandler =  signal(SIGSTOP, handler);
    if (oldhandler == SIG_ERR) {
        error(0, errno, "signal SIGSTOP");
    }

    for(;;) {

    }

    return 0;
}

