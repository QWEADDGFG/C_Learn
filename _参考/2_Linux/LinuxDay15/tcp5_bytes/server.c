#include <asm-generic/socket.h>
#include <func.h>

int main()
{
    //直接忽略掉SIGPIPE信号
    signal(SIGPIPE, SIG_IGN);

    //创建监听套接字
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(listenfd, -1, "socket");
    printf("listenfd: %d\n", listenfd);


    //设置套接字属性，网络地址可以重用
    int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
    ERROR_CHECK(ret, -1, "setsockopt");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));//初始化
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.30.129");

    //绑定网络地址
    ret = bind(listenfd, 
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

    //用户态定义的缓冲区
    char buff[128] = "hello,client";
    //第一次send
    ret = send(peerfd, buff, strlen(buff), 0);
    printf("send %d bytes.\n", ret);

    //第二次send
    ret = send(peerfd, buff, strlen(buff), 0);
    printf("send %d bytes.\n", ret);

    //第三次send
    ret = send(peerfd, buff, strlen(buff), 0);
    printf("send %d bytes.\n", ret);

    while(1);
    //close(peerfd);
    printf("close peerfd.\n");
    close(listenfd);

    return 0;
}

