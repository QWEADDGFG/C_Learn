#include <func.h>
#include <unistd.h>

int main()
{
    //创建UDP的套接字
    int serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK(serverfd, -1, "socket");

    //作为服务器需要绑定网络地址
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("192.168.30.129");

    int ret = bind(serverfd, 
                   (const struct sockaddr*)&serveraddr, sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "bind");


    //设置客户端的网络地址
    struct sockaddr_in clientaddr;
    memset(&clientaddr, 0, sizeof(clientaddr));
    socklen_t len = sizeof(clientaddr);
    char buff[128] = {0};
    //接收客户端的信息
    ret = recvfrom(serverfd, buff, sizeof(buff), 0, 
                       (struct sockaddr *)&clientaddr, &len);
    printf("recv from client: %s, ret:%d\n", buff, ret);
    printf("client: %s:%d\n", 
           inet_ntoa(clientaddr.sin_addr),
           ntohs(clientaddr.sin_port));

    //发送数据给客户端
    char buff2[] = "hello, client";
    ret = sendto(serverfd, buff2, strlen(buff2), 0, 
           (const struct sockaddr*)&clientaddr, sizeof(clientaddr));
    printf("send %d bytes.\n", ret);

    char buff3[] = "this is 2nd packet";
    ret = sendto(serverfd, buff3, strlen(buff3), 0, 
           (const struct sockaddr*)&clientaddr, sizeof(clientaddr));
    printf("send %d bytes.\n", ret);

    close(serverfd);

    return 0;
}

