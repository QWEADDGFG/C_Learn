#include <func.h>

int main(void)
{
    // ./test_getcwd 
    // char cwd[20];

    char* cwd;
    if ((cwd = getcwd(NULL, 0)) == NULL) {
        // 错误处理
        perror("getcwd");
        exit(1);
    }
    
    // getcwd一定成功
    puts(cwd);
    free(cwd);
    return 0;
}

