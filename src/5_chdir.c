#include "fun.h"
int main(int argc, char *argv[])
{
    // ./5_chdir.c dir1
    ARGS_CHECK(argc,2);
    printf("before , cwd = %s\n",getcwd(NULL,0));
    int ret =chdir(argv[1]);
    ERROR_CHECK(ret, -1, "chdir");
    printf("after , cwd = %s\n",getcwd(NULL,0));

    return 0;
}