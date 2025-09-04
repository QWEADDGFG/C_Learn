#include <func.h>

int sendFd(int pipefd, int fd, char exitFlag)
{
    //构建第二组成员, 传递进程池退出的标识位
    struct iovec iov;
    iov.iov_base = &exitFlag;
    iov.iov_len = 1;
    //构建第三组成员
    size_t len = CMSG_LEN(sizeof(fd));
    struct cmsghdr * cmsg = calloc(1, len);
    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    int * p = (int *)CMSG_DATA(cmsg);
    *p = fd;

    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsg;
    msg.msg_controllen = len;

    //发送数据
    int ret = sendmsg(pipefd, &msg, 0);
    printf("sendFd %d bytes.\n", ret);
    free(cmsg);//回收堆空间
    return 0;
}

int recvFd(int pipefd, int * pfd, char * pexitFlag)
{
    //exitFlag存储父进程传递过来的标识位信息
    char exitFlag = 0;
    //构建第二组成员
    struct iovec iov;
    iov.iov_base = &exitFlag;
    iov.iov_len = 1;
    //构建第三组成员
    size_t len = CMSG_LEN(sizeof(int));
    struct cmsghdr * cmsg = calloc(1, len);
    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;

    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsg;
    msg.msg_controllen = len;

    //接收数据, 默认情况下是阻塞的
    int ret = recvmsg(pipefd, &msg, 0);
    printf("recvFd %d bytes.\n", ret);
    *pfd = *(int*)CMSG_DATA(cmsg);
    *pexitFlag = exitFlag;//将标识位信息传递出去
    free(cmsg);//回收堆空间
    return 0;
}
