#include "fun.h"
int main(int argc, char *argv[])
{
    // ./7_rmdir.c dir
    ARGS_CHECK(argc, 2);
    int ret = rmdir(argv[1]);
    // 生成的目录权限受到umask掩码的影响
    ERROR_CHECK(ret, -1, "7_rmdir");
    return 0;
}