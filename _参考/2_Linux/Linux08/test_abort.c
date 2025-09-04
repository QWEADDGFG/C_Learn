#include <func.h>

// 执行一些资源清理操作
void func(void) {
    printf("I am going to die...");
}

int main(int argc, char* argv[])
{
    // 调用atexit()注册函数
    int err = atexit(func);
    if (err) {
        error(1, 0, "atexit");
    }

    // ...
    printf("Hello world");

    abort();

    printf("You cannot see me!\n");
}

