#include <func.h>

int sendFd(int pipefd, int fd);
int recvFd(int pipefd, int * pfd);

int main()
{
    int fds[2];
    socketpair(AF_LOCAL, SOCK_STREAM, 0, fds);


    pid_t pid = fork();
    if(pid > 0) {
        //父进程
        close(fds[0]);//父进程关闭读端
        int fd = open("file.txt", O_RDWR);
        printf("parent fd: %d\n", fd);
        ERROR_CHECK(fd, -1, "open");

        //将文件描述符fd发送给子进程
        //write(fds[1], &fd, sizeof(fd));
        sendFd(fds[1], fd);
    } else {
        //子进程
        close(fds[1]);//子进程关闭写端
        //从父进程获取一个fd
        int childFd;
        //read(fds[0], &childFd, sizeof(childFd));
        recvFd(fds[0], &childFd);
        printf("childFd:%d\n", childFd);
        printf("child fds[0]: %d\n", fds[0]);
        //从childFd中获取文件内容
        char buff[64] = {0};
        int ret = read(childFd, buff, sizeof(buff));
        printf("child read file content: %s\n", buff);

    }
    return 0;
}

