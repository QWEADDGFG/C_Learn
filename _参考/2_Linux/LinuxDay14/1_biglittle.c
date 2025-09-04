#include <func.h>

int test0()
{
    int num = 0x12345678;
    char * p = (char*)&num;
    printf("*p:%x\n", *p);

    return 0;
}

int test1()
{
    int num = 0x12345678;
    int netNum = htonl(num);
    printf("num:%x\n", num);
    printf("netNum:%x\n", netNum);

    
    unsigned short port =  8080;
    //把主机字节序转换为网络字节序
    unsigned short netPort = htons(port);
    printf("port:%x\n", port);
    printf("netPort:%x\n", netPort);

    //把网络字节序转换为主机字节序
    unsigned short port2 = ntohs(netPort);
    printf("port2:%x\n", port2);

    return 0;
}

int main(void)
{
    test1();
    return 0;
}
