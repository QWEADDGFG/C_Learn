#include "func.h"
#include <sys/select.h>

// ./bin/4_AZ 10.14.118.48 8080
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

    // accept
    // accept 从全连接队列中取出第一个连接请求，并创建一个新的socket与客户端通信，返回新的socket的文件描述符。
    // 如果全连接队列为空，则阻塞等待，直到有新的连接请求到来。<和read管道类似>
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr); // 需要初始化
    int connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    // accept(sockfd, NULL, NULL);
    printf("connect from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    fd_set rdset;
    char buf[1024];
    while (1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDERR_FILENO, &rdset);
        FD_SET(connfd, &rdset);
        select(connfd + 1, &rdset, NULL, NULL, NULL);
        if (FD_ISSET(STDERR_FILENO, &rdset))
        {
            // memset(buf, 0, sizeof(buf));
            bzero(buf, sizeof(buf));
            ssize_t sret = read(STDERR_FILENO, buf, sizeof(buf));
            if (sret == 0)
            {
                send(connfd, "exit", 4, 0);
                break;
            }
            send(connfd, buf, sret, 0);
        }
        if (FD_ISSET(connfd, &rdset))
        {
            bzero(buf, sizeof(buf));
            ssize_t sret = recv(connfd, buf, sizeof(buf), 0);
            if (sret == 0)
            {
                printf("cient close\n");
                break;
            }
            printf("recv: %s\n", buf);
        }
    }
    close(connfd);
    close(sockfd);

    return 0;
}