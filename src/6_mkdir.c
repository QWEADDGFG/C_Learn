#include "fun.h"
int main(int argc, char *argv[])
{
    // ./6_mkdir.c dir
    ARGS_CHECK(argc, 2);
    int ret = mkdir(argv[1], 0777);
    // 生成的目录权限受到umask掩码的影响
    ERROR_CHECK(ret, -1, "6_mkdir");
    return 0;
}