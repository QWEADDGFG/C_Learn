#include "fun.h"
int main(int argc, char *argv[])
{
    // ./3_chmod.c file1
    ARGS_CHECK(argc, 2);
    // int ret = chmod(argv[1], 0777);
    // int ret = chmod(argv[1], 0755);
    // int ret = chmod(argv[1], 0664);
    int ret = chmod(argv[1], 0600);
    ERROR_CHECK(ret, -1, "chmod");
    return 0;
}