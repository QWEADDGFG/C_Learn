#include <func.h>

int main(void)
{
    char cwd[20];

    if ((getcwd(NULL, 20)) == NULL) {
        // 错误处理
        error(1, errno, "getcwd");
    }
    
    // getcwd一定成功
    puts(cwd);
    return 0;
}

