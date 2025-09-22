#include "func.h"
#include <sys/select.h>

// ./bin/4_AZ_v2 10.14.118.48 8080
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    // create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // bind 固定IP地址和端口
    int ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, .1, "bind error");

    // listen
    // listen函数将socket变为监听状态，摧毁了socket的发送缓冲区与接收缓冲区，并开始监听来自客户端的连接请求，半连接队列与全连接队列的大小由listen函数的第二个参数指定。
    listen(sockfd, 10);

    fd_set rdset; //每次seleect监控的集合
    fd_set monitorset; // 下一次的监控集合
    FD_ZERO(&monitorset);
    FD_SET(sockfd, &monitorset);

    char buf[1024];
    int connfd;

    while (1)
    {
        memcpy(&rdset, &monitorset, sizeof(fd_set));
        select(10, &rdset, NULL, NULL, NULL); // 只修改rdset，不修改wrset和exset
        // 处理新连接
        if (FD_ISSET(sockfd, &rdset))
        {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
            printf("new connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            // 服务端在连上一个客户端，不和其他客户端通信
            FD_CLR(sockfd, &monitorset);
            FD_SET(STDIN_FILENO, &monitorset);
            FD_SET(connfd, &monitorset);
        }
        if (FD_ISSET(STDIN_FILENO, &rdset))
        {
            bzero(buf, sizeof(buf));
            ssize_t sret = read(STDIN_FILENO, buf, sizeof(buf));
            if (sret == 0) // 服务端断开连接
            {
                send(connfd, "server close", 13, 0);
                FD_SET(sockfd, &monitorset);
                FD_CLR(STDIN_FILENO, &monitorset);
                FD_CLR(connfd, &monitorset);
                close(connfd);
                printf("close connection\n");
                break;
            }
            send(connfd, buf, sret, 0);
        }
        if (FD_ISSET(connfd, &rdset))
        {
            bzero(buf, sizeof(buf));
            ssize_t sret = recv(connfd, buf, sizeof(buf), 0);
            if (sret == 0) // 客户端断开连接
            {
                printf("client close\n");
                FD_SET(sockfd, &monitorset);
                FD_CLR(STDIN_FILENO, &monitorset);
                FD_CLR(connfd, &monitorset);
                close(connfd);
                printf("close connection\n");
                continue;
            }
            printf("recv: %s\n", buf);
        }
    }

    return 0;
}