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

    int epfd = epoll_create(10); // epoll_create用于创建一个epoll实例, 取代定义fd_set
    struct epoll_event event;
    event.data.fd = STDIN_FILENO;
    event.events = EPOLLIN;                               // 监听stdin的可读事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event); // 注册事件到epoll实例中

    event.data.fd = connfd;
    event.events = EPOLLIN;                         // 监听connfd的可读事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event); // 注册事件到epoll实例中

    char buf[1024] = {0};

    while (1)
    {
        struct epoll_event ready_events[2];
        int num_ready_events = epoll_wait(epfd, ready_events, 2, -1); // 等待事件发生

        for (int i = 0; i < num_ready_events; ++i)
        {
            if (ready_events[i].data.fd == STDIN_FILENO)
            { // 如果stdin可读
                bzero(buf, sizeof(buf));
                ssize_t sret = read(STDIN_FILENO, buf, sizeof(buf)); // 读取stdin
                if (sret == 0)
                {
                    send(connfd, "exit", 4, 0); // 发送exit命令到客户端
                    goto end;
                }
                send(connfd, buf, sret, 0); // 发送stdin内容到客户端
            }
            else if (ready_events[i].data.fd == connfd)
            { // 如果connfd可读
                bzero(buf, sizeof(buf));
                ssize_t sret = recv(connfd, buf, sizeof(buf), 0); // 接收客户端内容
                if (sret == 0)
                {
                    printf("client closed\n");
                    goto end;
                }
                printf("recv: %s\n", buf); // 打印接收到的内容
            }
        }
    }
end:
    close(connfd);
    close(sockfd);
    close(epfd);
    return 0;
}