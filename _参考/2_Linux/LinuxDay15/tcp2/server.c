#include <func.h>

int main()
{
    //创建监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listenfd, -1, "socket");
    printf("listenfd: %d\n", listenfd);

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));//初始化
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.30.129");

    //绑定网络地址
    int ret = bind(listenfd, 
                   (const struct sockaddr*)&serveraddr, 
                   sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "bind");

    //进行监听
    ret = listen(listenfd, 10);
    ERROR_CHECK(ret, -1, "listen");
    printf("server start listening.\n");

    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    socklen_t len = sizeof(clientAddr);
    int peerfd = accept(listenfd, (struct sockaddr*)&clientAddr, &len);
    printf("%s:%d has connected, peerfd: %d.\n", 
           inet_ntoa(clientAddr.sin_addr),
           ntohs(clientAddr.sin_port), 
           peerfd);

    //当连接建立好之后，先休眠3秒
    sleep(5);

#if 0
    //用户态定义的缓冲区
    char buff[128] = "hello,client";
    ret = send(peerfd, buff, strlen(buff), 0);
    printf("send %d bytes.\n", ret);


    recv(peerfd, buff, sizeof(buff), 0);
    printf("recv msg: %s\n", buff);
#endif

    close(peerfd);
    close(listenfd);


    return 0;
}

