#include <func.h>

int test0()
{
    struct in_addr addr;
    const char * ip = "192.168.30.129";
    //将点分十进制的IP地址转换为网络字节序的IP地址
    inet_aton(ip, &addr);
    printf("addr.s_addr: %x\n", addr.s_addr);

    printf("netaddr:%x\n", inet_addr(ip));

    //将网络字节序的IP地址转换为点分十进制IP地址
    printf("ip: %s\n", inet_ntoa(addr));


    return 0;
}

void test1()
{
    //填充一个网络地址的方式
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = inet_addr("192.168.30.129");

    //打印网络地址
    printf("ip: %s, port: %d\n",
           inet_ntoa(addr.sin_addr),
           ntohs(addr.sin_port));

}

int main(void)
{
    test1();
    return 0;
}


