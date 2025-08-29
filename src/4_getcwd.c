#include "fun.h"
int main()
{
    // ./4_getcwd.c
    // char path[1024] = {0};
    // char *p = getcwd(path, sizeof(path));
    // ERROR_CHECK(path, NULL, "getcwd");
    // printf("cwd = %s\n", path);

    char *p = getcwd(NULL,0);
    printf("cwd2 = %s\n", p);
    return 0;
}