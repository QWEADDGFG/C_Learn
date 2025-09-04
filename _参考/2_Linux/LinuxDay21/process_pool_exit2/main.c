#include "process_pool.h"

int exitPipe[2]; void sighandler(int signum)
{
    printf("signum %d is coming.\n", signum);
    char ch = 1;
    write(exitPipe[1], &ch, sizeof(char));
}

int main(int argc, char ** argv)
{   // ip port processNum
    ARGS_CHECK(argc, 4);
    int processNum = atoi(argv[3]);
    // 创建存储进程池信息的结构体
    process_data_t * pProcess = calloc(processNum, sizeof(process_data_t));
    // 注册SIGPIPE信号
    signal(SIGPIPE, SIG_IGN);
    // 创建N个子进程
    makeChild(pProcess, processNum);

    //父进程的流程
    //父进程退出时，要处理SIGUSR1信号
    signal(SIGUSR1, sighandler);
    pipe(exitPipe);//创建要退出的匿名管道
    
    //创建监听套接字,并等待客户端的到来
    int listenfd = tcpInit(argv[1], argv[2]);

    //创建epoll的实例
    int epfd = epoll_create1(0);
    ERROR_CHECK(epfd, -1, "epoll_create1");
    //用epoll监听listenfd
    epollAddFd(epfd, listenfd);
    //用epoll监听父子进程间通信的管道
    for(int i = 0; i < processNum; ++i) {
        epollAddFd(epfd, pProcess[i].pipefd);
    }
    //用epoll监听要退出的匿名管道的读端
    epollAddFd(epfd, exitPipe[0]);

    struct epoll_event * pEventArr = 
        (struct epoll_event*)calloc(EVENT_ARR_SIZE, sizeof(struct epoll_event));

    //执行epoll的事件循环操作
    while(1){
        int nready = epoll_wait(epfd, pEventArr, EVENT_ARR_SIZE, 5000);

        for(int i = 0; i < nready; ++i) {
            int fd = pEventArr[i].data.fd;
            if(fd == listenfd) {//客户端有新连接到来
                int peerfd = accept(listenfd, NULL, NULL);
                printf("parent peerfd: %d\n", peerfd);

                //查找一个空闲的子进程去执行任务
                for(int j = 0; j < processNum; ++j) {
                    if(pProcess[j].status == FREE) {
                        //将peerfd装交给子进程进行处理
                        sendFd(pProcess[j].pipefd, peerfd, 0);
                        pProcess[j].status = BUSY;
                        break;
                    }
                }
                //关闭peerfd, 这里必须要加上
                //否则服务器这边连接不会正常断开
                close(peerfd);
            } else if(fd == exitPipe[0]) {
                printf("start exit2 process pool.\n");
                char exitFlag = 0;//读取退出的匿名管道中的数据
                read(exitPipe[0], &exitFlag, sizeof(exitFlag));
                printf("parent exitFlag:%d\n", exitFlag);
                for(int j = 0; j < processNum; ++j) {
                    sendFd(pProcess[j].pipefd, 0, exitFlag);
                }

                for(int j = 0; j < processNum; ++j) {
                    wait(NULL);//等待子进程退出
                    printf(">> wait return, j:%d.\n", j);
                }
            
                printf("end exit2 process pool.\n");
                close(epfd);
                close(listenfd);
                free(pProcess);
                exit(0);

            } else { //子进程发送完成之后，会通知父进程
                //fd 代表的是一条管道
                int howmany = 0;//对管道进行处理,否则默认情况下是水平触发，会一直通知
                int ret = read(fd, &howmany, sizeof(howmany));
                printf("ret: %d\n", ret);
                
                for(int j = 0; j < processNum; ++j) {
                    if(pProcess[j].pipefd == fd) {
                        pProcess[j].status = FREE;//更新子进程的状态
                        printf("child %d is not busy.\n", pProcess[j].pid);
                        break;
                    }
                }
            }
        }
    }

    return 0;
}

