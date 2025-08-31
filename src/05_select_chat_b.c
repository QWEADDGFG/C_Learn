#include "fun.h"

int main(int argc,char*argv[])
{
    int fd_read = open("1.pipe", O_RDONLY);
    int fd_write = open("2.pipe", O_WRONLY);


    // 初始化
    fd_set set;
    FD_ZERO(&set);

    char buf[60] = {0};

    while(1){
        // 注意: 下面两句代码放到while循环内部的原因是: 每次select之后监听集合set会被修改
        // 把文件描述符加入监听
        FD_SET(STDIN_FILENO, &set);
        FD_SET(fd_read, &set);
        // select: 监听那个文件读就绪
        select(10, &set, NULL, NULL, NULL);
        // select返回: set中包含就绪的文件描述符

        if(FD_ISSET(STDIN_FILENO, &set)){
            //标准输入可读: 读标准输入, 发送给对端
            bzero(buf, sizeof(buf));
            read(STDIN_FILENO, buf, sizeof(buf));
            write(fd_write, buf, sizeof(buf));
        }

        if(FD_ISSET(fd_read, &set)){
            bzero(buf, sizeof(buf));
            int res_read = read(fd_read, buf, sizeof(buf));
            if(res_read == 0){
                // 读就绪, 但是读出数据为0个, 说明对端关闭
                break;
            }
            printf("a: %s \n", buf);
        }
    }
    return 0;
}

