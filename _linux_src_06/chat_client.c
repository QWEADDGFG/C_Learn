#include "func.h"

volatile int running = 1;

void signal_handler(int sig)
{
    if (sig == SIGINT || sig == SIGTERM)
    {
        running = 0;
        printf("\n正在退出聊天室...\n");
    }
}

// ./bin/chat_client 10.14.118.48 8080
int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);

    // 注册信号处理函数
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // 创建socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(sockfd, -1, "socket error");

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));

    // 检查IP地址格式
    int ret = inet_aton(argv[1], &server_addr.sin_addr);
    if (ret == 0)
    {
        fprintf(stderr, "Invalid IP address: %s\n", argv[1]);
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // 连接服务器
    ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, -1, "connect error");

    printf("成功连接到聊天室服务器 %s:%s\n", argv[1], argv[2]);
    printf("输入消息并按回车发送，输入 'quit' 或按 Ctrl+C 退出\n");
    printf("----------------------------------------\n");

    // 创建epoll实例
    int epfd = epoll_create(10);
    ERROR_CHECK(epfd, -1, "epoll_create error");

    struct epoll_event event;

    // 添加socket到epoll监听
    event.data.fd = sockfd;
    event.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl add sockfd error");

    // 添加标准输入到epoll监听
    event.data.fd = STDIN_FILENO;
    event.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
    ERROR_CHECK(ret, -1, "epoll_ctl add stdin error");

    char send_buf[1024] = {0};
    char recv_buf[1024] = {0};
    time_t last_heartbeat = time(NULL);

    while (running)
    {
        struct epoll_event ready_events[10];
        int num_ready_events = epoll_wait(epfd, ready_events, 10, 1000); // 1秒超时

        if (num_ready_events == -1)
        {
            if (errno == EINTR)
            {
                continue; // 被信号中断，继续循环
            }
            perror("epoll_wait error");
            break;
        }

        for (int i = 0; i < num_ready_events; ++i)
        {
            if (ready_events[i].data.fd == sockfd)
            {
                // 从服务器接收消息
                memset(recv_buf, 0, sizeof(recv_buf));
                ssize_t recv_ret = recv(sockfd, recv_buf, sizeof(recv_buf) - 1, 0);

                if (recv_ret > 0)
                {
                    recv_buf[recv_ret] = '\0';
                    printf("收到消息: %s\n", recv_buf);
                    fflush(stdout);
                }
                else if (recv_ret == 0)
                {
                    printf("服务器已断开连接\n");
                    running = 0;
                    break;
                }
                else
                {
                    if (errno == EAGAIN || errno == EWOULDBLOCK)
                    {
                        continue; // 非阻塞模式下没有数据
                    }
                    perror("recv error");
                    running = 0;
                    break;
                }
            }
            else if (ready_events[i].data.fd == STDIN_FILENO)
            {
                // 从标准输入读取用户输入
                memset(send_buf, 0, sizeof(send_buf));
                if (fgets(send_buf, sizeof(send_buf), stdin) != NULL)
                {
                    // 去掉换行符
                    send_buf[strcspn(send_buf, "\n")] = '\0';

                    // 检查是否退出命令
                    if (strcmp(send_buf, "quit") == 0 || strcmp(send_buf, "exit") == 0)
                    {
                        printf("正在退出聊天室...\n");
                        running = 0;
                        break;
                    }

                    // 忽略空消息
                    if (strlen(send_buf) == 0)
                    {
                        continue;
                    }

                    // 发送消息到服务器
                    ssize_t send_ret = send(sockfd, send_buf, strlen(send_buf), 0);
                    if (send_ret == -1)
                    {
                        perror("send error");
                        running = 0;
                        break;
                    }

                    printf("已发送: %s\n", send_buf);
                }
            }
        }

        // 发送心跳包保持连接活跃
        time_t current_time = time(NULL);
        if (current_time - last_heartbeat >= 3)
        {
            // 每3秒发送一个心跳包（空消息）
            char heartbeat[] = "";
            ssize_t send_ret = send(sockfd, heartbeat, strlen(heartbeat), 0);
            if (send_ret == -1)
            {
                perror("heartbeat send error");
                running = 0;
                break;
            }
            last_heartbeat = current_time;
        }
    }

    // 清理资源
    close(epfd);
    close(sockfd);
    printf("已断开与聊天室的连接\n");

    return 0;
}