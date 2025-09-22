#include "func.h"

typedef struct connection_s
{
    int connfd;
    int is_online;
    time_t last_active_time;
} connection_t;

// ./bin/7_epoll_chat_room  10.14.118.48 8080
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    // create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    int reuse = 1;
    int ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    ERROR_CHECK(ret, .2, "setsockopt error");

    // bind 固定IP地址和端口
    ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, .1, "bind error");

    // listen
    // listen函数将socket变为监听状态，摧毁了socket的发送缓冲区与接收缓冲区，并开始监听来自客户端的连接请求，半连接队列与全连接队列的大小由listen函数的第二个参数指定。
    listen(sockfd, 10);

    connection_t connections_client[1024];
    int curr_conn_idx = 0;
    char buf[1024] = {0};

    // create epoll
    int epfd = epoll_create(10); // epoll_create用于创建一个epoll实例, 取代定义fd_set
    struct epoll_event event;
    event.data.fd = sockfd;
    event.events = EPOLLIN;                         // 监听stdin的可读事件
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event); // 注册事件到epoll实例中

    time_t curtime;

    while (1)
    {
        struct epoll_event ready_events[1024];
        int num_ready_events = epoll_wait(epfd, ready_events, 1024, 1000); // 等待事件发生1000ms

        for (int i = 0; i < num_ready_events; ++i)
        {
            if (ready_events[i].data.fd == sockfd)
            {
                struct sockaddr_in client_addr;
                socklen_t client_addr_len = sizeof(client_addr);
                int connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
                printf("new connection: %d\n", connfd);
                printf("client ip: %s, port: %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
                connections_client[curr_conn_idx].connfd = connfd;
                connections_client[curr_conn_idx].is_online = 1;                 // 1表示在线，0表示离线
                connections_client[curr_conn_idx].last_active_time = time(NULL); // 初始化活跃时间

                event.data.fd = connfd;
                // event.events = EPOLLIN | EPOLLET;               // 监听连接的可读事件,边缘触发一般不使用
                event.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event); // 注册事件到epoll实例中
                curr_conn_idx++;
            }
            else
            {
                // 从ready_events[i].data.fd 中读取数据，转发给其余在线的客户端
                bzero(buf, sizeof(buf));
                ssize_t sret = recv(ready_events[i].data.fd, buf, sizeof(buf), 0);
                if (sret == 0)
                {
                    for (int j = 0; j < curr_conn_idx; j++)
                    {
                        if (connections_client[j].connfd == ready_events[i].data.fd && connections_client[j].is_online == 1)
                        {
                            connections_client[j].is_online = 0; // 标记为离线
                            printf("connection %d offline\n", connections_client[j].connfd);
                            epoll_ctl(epfd, EPOLL_CTL_DEL, connections_client[j].connfd, NULL); // 从epoll实例中删除事件
                            close(connections_client[j].connfd);                                // 关闭连接
                            break;
                        }
                    }
                }
                for (int j = 0; j < curr_conn_idx; j++)
                {
                    if (connections_client[j].connfd == ready_events[i].data.fd || connections_client[j].is_online == 0)
                    {
                        continue; // 跳过离线的连接
                    }
                    send(connections_client[j].connfd, buf, strlen(buf), 0); // 转发数据
                }
                int connfd = ready_events[i].data.fd;
            }
            for (int j = 0; j < curr_conn_idx; j++)
            {
                if (connections_client[j].connfd == ready_events[i].data.fd && connections_client[j].is_online == 1)
                {
                    connections_client[j].last_active_time = time(NULL); // 更新活跃时间
                    break;
                }
            }
        }
        curtime = time(NULL);
        printf("curtime: %s\n", ctime(&curtime));
        for (int i = 0; i < curr_conn_idx; i++)
        {
            if (connections_client[i].is_online == 1 && connections_client[i].last_active_time + 5 < curtime)
            {
                connections_client[i].is_online = 0; // 标记为离线
                printf("connection %d offline\n", connections_client[i].connfd);
                epoll_ctl(epfd, EPOLL_CTL_DEL, connections_client[i].connfd, NULL); // 从epoll实例中删除事件
                close(connections_client[i].connfd);                                // 关闭连接
            }
        }
    }

    return 0;
}