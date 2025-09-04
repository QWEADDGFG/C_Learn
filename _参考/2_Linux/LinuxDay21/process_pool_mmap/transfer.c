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
    char * pMap = mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if(pMap) {
        printf("pMap: %x\n", pMap);
        //pMap代表的是内核中的文件缓冲区
        //peerfd代表的是套接字缓冲区
        int ret = send(peerfd, pMap, st.st_size, 0);
        printf("ret: %d, send file over.\n", ret);
    }

    close(fd);//关闭文件
    return 0;
}

