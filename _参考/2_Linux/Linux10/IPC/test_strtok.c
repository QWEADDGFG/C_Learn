#include <func.h>

#define MAXLINE 256
#define MAXARGS 64

int main(int argc, char* argv[])
{
    char input[MAXLINE];
    char* args[MAXARGS];

    fgets(input, MAXLINE, stdin);
    
    // 解析命令
    int i = 0;
    args[i] = strtok(input, " \t\n");

    while (args[i] != NULL) {
        args[++i] = strtok(NULL, " \t\n");
    } // args[i] = NULL;

    char** p = args;
    while (*p != NULL) {
        puts(*p); // 打印每一个参数
        p++;
    }
    return 0;
}

