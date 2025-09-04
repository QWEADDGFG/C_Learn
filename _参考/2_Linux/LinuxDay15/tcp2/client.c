#include <func.h>

int main()
{
    //创建客户端套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");
    printf("clientfd: %d\n", clientfd);

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));//初始化
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.30.129");

    int ret = connect(clientfd, 
                      (const struct sockaddr *)&serveraddr, 
                      sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "connect");

    printf("connect success\n");
    while(1);

    //用户态定义的接收缓冲区
    char buff[128] = {0};
    ret = recv(clientfd, buff, sizeof(buff), 0);
    printf("ret: %d, recv msg: %s\n", ret, buff);
    

    //用户态定义的发送缓冲区
    char buff2[128] = "hello,server";
    ret = send(clientfd, buff2, strlen(buff2), 0);
    printf("send %d bytes.\n", ret);

    close(clientfd);

    return 0;
}

