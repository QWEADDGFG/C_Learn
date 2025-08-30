#include "fun.h"
int main(int argc, char *argv[])
{
    // ./4_read_stdin
    ARGS_CHECK(argc, 1);
    char buf[1024] = {0};
    ssize_t sret = read(0, buf, sizeof(buf));
    ERROR_CHECK(sret, -1, "read");
    printf("sret = %ld, buf = %s\n", sret, buf);
    return 0;
}