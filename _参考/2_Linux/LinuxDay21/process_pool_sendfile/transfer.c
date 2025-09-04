#include "process_pool.h"

#define FILENAME "bigfile.avi"

int sendn(int sockfd, const void * buff, int len)
{
    int left = len;
    const char * pbuf = buff;
    int ret = 0;
    while(left > 0) {
        ret = send(sockfd, pbuf, left, 0);
        if(ret == -1) {
            perror("send");
            return -1;
        }
        pbuf += ret;
        left -= ret;
    }
    return len - left;
}

int transferFile(int peerfd)
{
    //读取本地文件
    int fd = open(FILENAME, O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    train_t t;
    memset(&t, 0, sizeof(t));
    //先发送文件名
    t.len = strlen(FILENAME);
    strcpy(t.buff, FILENAME);
    send(peerfd, &t, 4 + t.len, 0);

    //其次发送文件长度
    struct stat st;
    memset(&st, 0, sizeof(st));
    fstat(fd, &st);
    printf("filelength: %ld\n", st.st_size);//off_t
    printf("sizeof(st.st_size): %ld\n", sizeof(st.st_size));
    send(peerfd, &st.st_size, sizeof(st.st_size), 0);
    
    //最后发送文件内容
    int ret = sendfile(peerfd, fd, NULL, st.st_size);
    printf("send %d bytes.\n", ret);
    close(fd);//关闭文件
    return 0;
}

