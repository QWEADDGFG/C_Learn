#include <func.h>

int g_value = 10;  // 数据段
int main(int argc, char* argv[])
{
    int l_value = 20;   // 栈
    int* d_value = (int*)malloc(sizeof(int)); // 堆
    *d_value = 30;

    pid_t pid = fork();
    switch (pid) {
    case -1:
        error(1, errno, "fork");
    case 0:
        // 子进程
        g_value += 100;
        l_value += 100;
        *d_value += 100;
        printf("g_value = %d, l_value = %d, d_value = %d\n", g_value, l_value, *d_value);
        exit(0);
    default:
        // 父进程
        sleep(2);
        printf("g_value = %d, l_value = %d, d_value = %d\n", g_value, l_value, *d_value);
        exit(0);
    }
    return 0;
}

