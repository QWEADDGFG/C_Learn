#include "func.h"

// ./bin/3_server 10.14.118.48 8080 <只能绑定到本地的IP地址> 等价与 ./bin/3_server 0.0.0.0 8080
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

    // send/recv
    char buf[1024] = {0};
    ssize_t sret = recv(connfd, buf, sizeof(buf), 0);
    printf("sret=%ld, recv: %s\n", sret, buf);
    return 0;
}