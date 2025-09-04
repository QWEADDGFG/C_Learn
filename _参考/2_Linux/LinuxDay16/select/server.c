#include <func.h>

#define CONNS_MAX 1024

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

    
    fd_set rdset;
    printf("sizeof(rdset): %ld\n", sizeof(rdset));
    FD_ZERO(&rdset);
    char buff[1000] = {0};
    int maxfd = listenfd;

    //conns存储的是已经建立好的连接peerfd
    int conns[CONNS_MAX] = {0};

    //对IO事件进行监听
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(listenfd, &rdset);//对监听套接字listenfd进行监听
        //对已经建立好的连接进行监听
        for(int i = 0; i < CONNS_MAX; ++i) {
            if(conns[i] !=0) {
                FD_SET(conns[i], &rdset);
            }
        }

        //select是一个阻塞式函数
        printf("before selete.\n");
        int n = select(maxfd + 1, &rdset, NULL, NULL, NULL);
        printf("n: %d\n", n);

        //判断是否有新连接过来
        if(FD_ISSET(listenfd, &rdset)) {
            struct sockaddr_in clientAddr;
            memset(&clientAddr, 0, sizeof(clientAddr));
            socklen_t len = sizeof(clientAddr);
            int peerfd = accept(listenfd, (struct sockaddr*)&clientAddr, &len);
            printf("%s:%d has connected, peerfd: %d.\n", 
                   inet_ntoa(clientAddr.sin_addr),
                   ntohs(clientAddr.sin_port), 
                   peerfd);
            //存储已经建立好的连接
            for(int i = 0; i < CONNS_MAX; ++i) {
                if(conns[i] == 0) {
                    conns[i] = peerfd;
                    break;
                }
            }
            //更新maxfd的值
            if(maxfd < peerfd) {
                maxfd = peerfd;
            }

        }
        //对已经建立好的连接peerfd进行处理
        //需要遍历conns数组，查看peerfd是否就绪
        for(int i = 0; i < CONNS_MAX; ++i) {
            if(conns[i] != 0) {
                if(FD_ISSET(conns[i], &rdset)) {
                    //清空缓冲区
                    memset(buff, 0, sizeof(buff));
                    //从对端获取数据
                    int ret = recv(conns[i], buff, sizeof(buff), 0);
                    printf("ret: %d\n", ret);
                    if(ret == 0) {
                        //连接已经断开了
                        close(conns[i]);
                        conns[i] = 0;
                        continue;
                    }
                    printf("recv msg: %s\n", buff);
                    //回显操作
                    send(conns[i], buff, strlen(buff), 0);
                }
            }
        }

    }
    printf("byebye.\n");

    close(listenfd);

    return 0;
}

