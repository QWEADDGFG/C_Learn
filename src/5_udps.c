#include "func.h"

// ./bin/5_udps 0.0.0.0 8080
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // 创建套接字, udp使用SOCK_DGRAM，tcp使用SOCK_STREAM
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr)); // 初始化地址结构体
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));                                  // 端口号
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);                             // IP地址
    int ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // 绑定地址
    ERROR_CHECK(ret, -1, "bind error");

    // 接收数据
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    char recv_buf[1024] = {0};
    recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&client_addr, &len);
    printf("recv from %s:%d, data: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), recv_buf);

    sendto(sockfd, "hello", 6, 0, (struct sockaddr *)&client_addr, len); // 发送数据
    sendto(sockfd, "world", 6, 0, (struct sockaddr *)&client_addr, len); // 发送数据
    close(sockfd);

    return 0;
}