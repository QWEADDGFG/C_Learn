#include <func.h>

#define FOO()                   \
do {                            \
    printf("I love xixi\n");    \
    printf("I love xixi\n");    \
    printf("I love xixi\n");    \
} while(0)

int main(int argc, char* argv[])
{
    int flag = 1;
    if (flag)
        FOO();
    else 
        printf("I love liuyifei\n");

    return 0;
}

