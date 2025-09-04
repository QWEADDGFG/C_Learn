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

    //设置套接字属性，网络地址可以重用
    int on = 1;
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(int));
    ERROR_CHECK(ret, -1, "setsockopt");

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
    
    fd_set rdset;
    printf("sizeof(rdset): %d\n", sizeof(rdset));
    FD_ZERO(&rdset);
    char buff[1000] = {0};

    //对IO事件进行监听
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(peerfd, &rdset);
        FD_SET(STDIN_FILENO, &rdset);

        select(peerfd + 1, &rdset, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &rdset)) {
            //清空缓冲区
            memset(buff, 0, sizeof(buff));
            //从标准输入获取数据
            int ret = read(STDIN_FILENO, buff, sizeof(buff));
            if(ret == 0) {
                break;
            }
            printf("read ret: %d\n", ret);
            
            //发送给对端
            ret = send(peerfd, buff, strlen(buff), 0);
            printf("send %d bytes.\n", ret);
        }

        if(FD_ISSET(peerfd, &rdset)) {
            //清空缓冲区
            memset(buff, 0, sizeof(buff));
            //从对端获取数据
            int ret = recv(peerfd, buff, sizeof(buff), 0);
            if(ret == 0) {
                //连接已经断开了
                break;
            }
            printf("recv msg: %s\n", buff);
        }
    }
    printf("byebye.\n");

    close(peerfd);
    close(listenfd);

    return 0;
}

