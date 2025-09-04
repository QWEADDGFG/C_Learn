#include <func.h>
#include <sys/select.h>
#include <unistd.h>

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

    fd_set rdset;
    FD_ZERO(&rdset);
    char buff[1000] = {0};

    //对IO事件进行监听
    while(1) {
        FD_ZERO(&rdset);
        FD_SET(clientfd, &rdset);
        FD_SET(STDIN_FILENO, &rdset);

        select(clientfd + 1, &rdset, NULL, NULL, NULL);

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
            ret = send(clientfd, buff, strlen(buff), 0);
            printf("send %d bytes.\n", ret);
        }

        if(FD_ISSET(clientfd, &rdset)) {
            //清空缓冲区
            memset(buff, 0, sizeof(buff));
            //从对端获取数据
            int ret = recv(clientfd, buff, sizeof(buff), 0);
            if(ret == 0) {
                //连接已经断开了
                break;
            }
            printf("recv msg: %s\n", buff);
        }
    }
    printf("byebye.\n");

    close(clientfd);

    return 0;
}

