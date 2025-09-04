#include <func.h>

//接收确定个字节的数据
int recvn(int sockfd, void * buff, int len)
{
    int left = len;
    char * pbuf = buff;
    int ret = 0;
    while(left > 0) {
        ret = recv(sockfd, pbuf, left, 0);
        if(ret < 0) {
            perror("recv");
            break;
        } else if (ret == 0) {
            break;
        }
        pbuf += ret;
        left -= ret;
    }
    return len - left;
}

int main()
{
    //创建客户端套接字
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK(clientfd, -1, "socket");

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));//初始化
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(8080);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int ret = connect(clientfd, 
                      (const struct sockaddr *)&serveraddr, 
                      sizeof(serveraddr));
    ERROR_CHECK(ret, -1, "connect");

    //先接收文件名
    char filename[100] = {0};
    int len = 0;
    ret = recvn(clientfd, (char*)&len, sizeof(len));//先接长度
    printf("ret: %d, filename's len:%d\n", ret, len);
    ret = recvn(clientfd, filename, len);//再接内容
    printf("ret: %d, recv msg:%s\n", ret, filename);
    
    int wfd = open(filename, O_CREAT | O_RDWR, 0644);
    ERROR_CHECK(wfd, -1, "open");

    //再获取的是文件长度
    off_t length = 0;
    recvn(clientfd, (char*)&length, sizeof(length));
    printf("file length: %ld\n", length);
    //最后接收文件内容
    char buff[1000] = {0};
    while(1) {
        ret = recvn(clientfd, (char*)&len, sizeof(len));//先接长度
        if(len != 1000) {
            printf("len: %d\n", len);
        }
        if(ret == 0) {
            break;
        }
        //将recv函数的第四个参数设置为MSG_WAITALL
        //可以确定接收len个字节的长度
        ret = recvn(clientfd, buff, len);//再接文件内容
        if(ret != 1000) {
            printf("ret: %d\n", ret);
        }
        //printf("ret:%d, recv msg:%s\n", ret, buff);
        //最后再写入本地
        write(wfd, buff, ret);
    }
    close(wfd);
    close(clientfd);

    return 0;
}

