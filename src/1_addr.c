#include "func.h"

// ./bin/demo 192.168.118.128 1234
// port=d204, ip=8076a8c0

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;//IPv4
    addr.sin_port = htons(atoi(argv[2]));//port
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    printf("port=%x, ip=%x\n",addr.sin_port,addr.sin_addr.s_addr);
    return 0;
}