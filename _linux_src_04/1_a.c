#include "fun.h"
// 1_a.c 负责将文件的名字，长度和内容通过管道发送给1_b.c
typedef struct train_s
{
    int length;
    char data[1000];
} train_t;

int main(int argc, char *argv[])
{
    // ./1_a.c pipe_name file_name
    ARGS_CHECK(argc, 3);
    int fdw_pipe = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw_pipe, -1, "open pipe");

    train_t train;
    train.length = strlen(argv[2]);
    memcpy(train.data, argv[2], train.length);
    write(fdw_pipe, &train, sizeof(train.length));
    write(fdw_pipe, train.data, train.length);

    int fdr_file = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr_file, -1, "open file");
    ssize_t sret = read(fdr_file, train.data, sizeof(train.data));
    train.length = sret;
    write(fdw_pipe, &train, sizeof(train.length));
    write(fdw_pipe, train.data, train.length);

    close(fdw_pipe);
    close(fdr_file);
    return 0;
}
//(base) root@davinci-mini:/home/HwHiAiUser/gp/C_C++/C_Learn# ./bin/1_a 1.pipe file1