#include <func.h>
#include <sys/epoll.h>

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


    //创建epoll的实例
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create1");
    
    //对相应的文件描述符进行监听
    struct epoll_event ev;
    ev.events = EPOLLIN;//关注listenfd的读事件
    ev.data.fd = listenfd;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    ERROR_CHECK(ret, -1, "epoll_ctl");
    struct epoll_event * pEventArr = calloc(CONNS_MAX, sizeof(struct epoll_event));

    //执行事件循环
    while(1) {
        int nready = epoll_wait(epfd, pEventArr, CONNS_MAX, -1);
        if(nready == -1 && errno == EINTR) {
            continue;
        } else if(nready == 0) {
            printf("timeout.\n");
        } else if(nready == -1) {
            break;
        } else {
            //nready > 0的情况
            //对nready个文件描述符进行处理
            for(int i = 0; i < nready; ++i) {
                int fd = pEventArr[i].data.fd;
                //对listenfd的处理, 建立新的连接
                if(fd == listenfd) {
                    struct sockaddr_in clientAddr;
                    memset(&clientAddr, 0, sizeof(clientAddr));
                    socklen_t len = sizeof(clientAddr);
                    int peerfd = accept(listenfd, (struct sockaddr*)&clientAddr, &len);
                    printf("%s:%d has connected, peerfd: %d.\n", 
                           inet_ntoa(clientAddr.sin_addr),
                           ntohs(clientAddr.sin_port), 
                           peerfd);

                    struct epoll_event ev;
                    //采用边缘触发
                    ev.events = EPOLLIN | EPOLLET;//关注peerfd的读事件
                    ev.data.fd = peerfd;    
                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, peerfd, &ev);

                } else {
                    //对peerfd的处理
                    //判断是否发生了读事件
                    if(pEventArr[i].events & EPOLLIN) {
                        char buff[1024] = {0};
                    
                        //先去内核接收缓冲区中看一眼，有多少数据
                        //但并不移走内核接收缓冲区的数据
                        int ret = recv(fd, buff, sizeof(buff), MSG_PEEK);
                        if(ret == 0) {
                            //连接断开的情况
                            ev.data.fd = fd;//从监听的红黑树删除掉
                            ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
                            ERROR_CHECK(ret, -1, "epoll_ctl");
                            close(fd);//关闭连接
                            printf("byebye.\n");
                            continue;
                        }
                        printf("ret:%d, msg:%s\n", ret, buff);

                        if(ret > 15) {
                            //当内核缓冲区中的数据长度大于15个字节时，
                            //才进行消息的处理
                            //执行该操作，会移走内核中的数据
                            recv(fd, buff, ret, 0);
                            //执行回显操作
                            send(fd, buff, strlen(buff), 0);
                        }
                    }
                }
            }
        }
    }


    

    close(listenfd);
    close(epfd);

    return 0;
}

