#include <func.h>
#include <netdb.h>

int main(int argc, char ** argv)
{
    //const char * domain = "www.baidu.com";
    struct hostent * pHost = gethostbyname(argv[1]);
    printf("h_name: %s\n", pHost->h_name);
    for(int i = 0; pHost->h_aliases[i] != NULL; ++i) {
        printf("alias[%d]: %s\n", i, pHost->h_aliases[i]);
    }

    int addrType = pHost->h_addrtype;
    printf("addr type: %d\n", addrType);
    printf("addr length: %d\n", pHost->h_length);

    for(int i = 0; pHost->h_addr_list[i] != NULL; ++i) {
        char buff[60] = {0};
        inet_ntop(addrType, pHost->h_addr_list[i], buff, sizeof(buff));
        printf("ip[%d]: %s\n", i, buff);
    }

    return 0;
}

