#include "thread_pool.h"

//每一个子线程的线程函数入口
void * threadFunc(void * arg)
{
    //先获取到线程池
    threadpool_t * threadpool = (threadpool_t*)arg;
    while(1) {
        //当队列中有节点时，获取任务节点
        //当队列中没有节点时，就阻塞在这里
        int peerfd = taskDequeue(&threadpool->queue);
        if(peerfd > 0) {
            //传输文件
            transferFile(peerfd);
            //关闭连接
            close(peerfd);
        } else {
            break;//退出子线程
        }
    }
    return NULL;
}

void threadpoolInit(threadpool_t * threadpool, int num)
{
    if(threadpool) {
        threadpool->pthreads = (pthread_t*) calloc(num, sizeof(pthread_t));
        threadpool->threadNum = num;
        queueInit(&threadpool->queue);
    }
}

void threadpoolDestroy(threadpool_t *threadpool)
{
    if(threadpool) {
        free(threadpool->pthreads);
        queueDestroy(&threadpool->queue);
    }
}

void threadpoolStart(threadpool_t *threadpool)
{
    if(threadpool) {
        for(int i = 0; i < threadpool->threadNum; ++i) {
            int ret = pthread_create(
                        &threadpool->pthreads[i], 
                        NULL, 
                        threadFunc, 
                        threadpool);
            THREAD_ERROR_CHECK(ret, "pthread_create");
            printf("sub thread %ld\n", threadpool->pthreads[i]);
        }
    }
}

void threadpoolStop(threadpool_t * threadpool)
{
    //当任务队列中还有元素时,应该要继续执行
    while(!queueIsEmpty(&threadpool->queue)) {
        sleep(1);
    }

    //通知所有的子线程退出
    broadcastAll(&threadpool->queue);
    //回收子线程的资源
    for(int i = 0; i < threadpool->threadNum; ++i) {
        pthread_join(threadpool->pthreads[i], NULL);
        printf("sub thread %ld join.\n", threadpool->pthreads[i]);
    }
}
