#include "func.h"
#include <sys/select.h>

// ./bin/4_AQ 10.14.118.48 8080
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

    fd_set rdset;
    char buf[1024];
    while (1)
    {
        FD_ZERO(&rdset);
        FD_SET(STDERR_FILENO, &rdset);
        FD_SET(sockfd, &rdset);
        select(sockfd + 1, &rdset, NULL, NULL, NULL);
        if (FD_ISSET(STDERR_FILENO, &rdset))
        {
            // memset(buf, 0, sizeof(buf));
            bzero(buf, sizeof(buf));
            ssize_t sret = read(STDERR_FILENO, buf, sizeof(buf));
            if (sret == 0)
            {
                send(sockfd, "exit", 4, 0);
                break;
            }
            send(sockfd, buf, sret, 0);
        }
        if (FD_ISSET(sockfd, &rdset))
        {
            bzero(buf, sizeof(buf));
            ssize_t sret = recv(sockfd, buf, sizeof(buf), 0);
            if (sret == 0)
            {
                printf("server close\n");
                break;
            }
            printf("recv: %s\n", buf);
        }
    }
    close(sockfd);

    return 0;
}