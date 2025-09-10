#include "fun.h"
// 1_b.c 需要新建一个目录，并将该文件存储起来
typedef struct train_s
{
    int length;
    char data[1000];
} train_t;

int main(int argc, char *argv[])
{
    // ./1_b pipe_name
    ARGS_CHECK(argc, 2);
    int fdr_pipe = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr_pipe, -1, "open");

    train_t train;
    read(fdr_pipe, &train.length, sizeof(train.length));
    read(fdr_pipe, train.data, train.length);
    printf("length:%d, data:%s\n", train.length, train.data);
    char file_name[100] = {0};
    memcpy(file_name, train.data, train.length);
    char path[8192] = {0};
    char dir[] = "./dir1/";
    mkdir(dir, 0777);
    sprintf(path, "%s%s%s", dir, "/", file_name);
    int fdw_file = open(path, O_WRONLY | O_CREAT, 0666);
    ERROR_CHECK(fdw_file, -1, "open");
    read(fdr_pipe, &train.length, sizeof(train.length));
    read(fdr_pipe, train.data, train.length);
    write(fdw_file, train.data, train.length);
    close(fdw_file);
    close(fdr_pipe);
    return 0;
}
// (base) root@davinci-mini:/home/HwHiAiUser/gp/C_C++/C_Learn# cat dir1/file1
// (base) root@davinci-mini:/home/HwHiAiUser/gp/C_C++/C_Learn# ./bin/1_b 1.pipe 
// length:5, data:file1
// (base) root@davinci-mini:/home/HwHiAiUser/gp/C_C++/C_Learn# cat dir1/file1
// hello(base) root@davinci-mini:/home/HwHiAiUser/gp/C_C++/C_Learn# tree dir1/
// dir1/
// └── file1

// 0 directories, 1 file
// (base) root@davinci-mini:/home/HwHiAiUser/gp/C_C++/C_Learn# 