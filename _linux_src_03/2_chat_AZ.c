#include "fun.h"
int main(int argc, char *argv[])
{
    // ./2_chat_AZ 1.pipe 2.pipe
    ARGS_CHECK(argc, 3);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open");
    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open");
    printf("阿珍 chat start\n");

    char buf[4096];
    fd_set rdset;
    while (1)
    {
        // select之前必须先清空rdset
        FD_ZERO(&rdset);
        // 现在fd_set是监听集合，将STDIN_FILENO和fdr加入到监听集合中
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);
        struct timeval timeout = {5, 0}; // 设置超时时间为5秒
        // select函数会阻塞，直到有数据可读或超时
        int ret = select(fdr + 1, &rdset, NULL, NULL, &timeout);
        // select返回后，判断是否有数据可读 就绪集合
        if (ret == 0)
        {
            printf("timeout\n");
            time_t now = time(NULL);
            printf("time:%s", ctime(&now));
            continue;
        }
        if (FD_ISSET(STDIN_FILENO, &rdset))
        { // 读取用户输入
            memset(buf, 0, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf));
            write(fdw, buf, strlen(buf));
        }
        if (FD_ISSET(fdr, &rdset))
        { // 管道就绪，读取阿珍的消息
            memset(buf, 0, sizeof(buf));
            ssize_t sret = read(fdr, buf, sizeof(buf));
            if (sret == 0)
            { // 管道关闭，退出
                printf("chat end\n");
                break;
            }
            printf("阿强:%s", buf);
        }
    }
    close(fdr);
    close(fdw);
    return 0;
}