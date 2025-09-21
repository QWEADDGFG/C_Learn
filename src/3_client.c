#include "func.h"

// ./bin/3_client 10.14.118.48 8080
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // connect 建立连接 发起第一次握手
    int ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, -1, "connect error");

    // send 只是一个特殊的write操作，只能对socket使用
    // send/recv 将数据在buf和socket之间移动，直到buf被填满或socket被关闭
    ssize_t sret = send(sockfd, "hello world", 11, 0);
    printf("sret=%ld \n", sret);

    return 0;
}