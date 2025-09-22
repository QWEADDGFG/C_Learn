#include "func.h"

// ./bin/5_udpc 10.14.118.48 8080
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // 创建套接字, udp使用SOCK_DGRAM，tcp使用SOCK_STREAM
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr)); // 初始化地址结构体
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));      // 端口号
    server_addr.sin_addr.s_addr = inet_addr(argv[1]); // IP地址

    // 客户端先发送数据
    sendto(sockfd, "zaima", 5, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char recv_buf[1024];
    int len = recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&server_addr, &len);
    printf("recv_buf:%s\n", recv_buf);
    close(sockfd);

    return 0;
}