#include <func.h>

int main(int argc, char* argv[])
{
    // ./test_chdir path
    if (argc != 2) {
        error(1, 0, "Usage: %s path", argv[0]);
    }

    char cwd[128];
    getcwd(cwd, 128);
    puts(cwd);

    // 惯用法：切换当前工作目录
    if (chdir(argv[1]) == -1) {
        error(1, errno, "chdir %s", argv[1]);
    }

    getcwd(cwd, 128);
    puts(cwd);
    return 0;
}

