#include "func.h"

/*使用条件变量实现生产者消费者模型*/

typedef struct node_s
{
    int data;
    struct node_s *next;
} node_t;

typedef struct queue_s
{
    node_t *pHead;
    node_t *pTail;
    int queueSize;
} queue_t;

typedef struct shareRes_s // 共享资源包含队列，锁，条件变量
{
    queue_t queue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} shareRes_t;

int enQueue(queue_t *pQueue, int data) // 尾插法--入队
{
    node_t *pNew = (node_t *)calloc(1, sizeof(node_t)); // 在堆上分配内存
    pNew->data = data;
    if (pQueue->queueSize == 0)
    {
        pQueue->pHead = pNew;
        pQueue->pTail = pNew;
    }
    else
    {
        pQueue->pTail->next = pNew;
        pQueue->pTail = pNew;
    }
    pQueue->queueSize++;
    return 0;
}

int deQueue(queue_t *pQueue) // 头部删除法--出队
{
    node_t *pDel = pQueue->pHead;
    pQueue->pHead = pQueue->pHead->next;

    if (pQueue->queueSize == 1)
    {
        pQueue->pTail = NULL;
    }
    free(pDel);
    --pQueue->queueSize;
    return 0;
}

int visitQueue(queue_t *pQueue) // 遍历队列
{
    node_t *pTmp = pQueue->pHead;
    while (pTmp)
    {
        printf("%d ", pTmp->data);
        pTmp = pTmp->next;
    }
    printf("\n");
    return 0;
}

/*单元测试--队列的增删与打印*/
// int main(int argc, char *argv[])
// {
//     queue_t myQueue;
//     memset(&myQueue, 0, sizeof(queue_t)); // 初始化队列
//     for (int i = 1; i <= 5; i++)
//     {
//         int data = rand() % 100; // 生成随机数
//         printf("enqueue %d\n", data);
//         enQueue(&myQueue, data);
//         visitQueue(&myQueue); // 打印队列
//     }
//     printf("---------------------------\n");
//     for (int i = 0; i < 5; i++)

//     {
//         int head = myQueue.pHead->data;
//         printf("dequeue %d\n", head);
//         deQueue(&myQueue);    // 出队
//         visitQueue(&myQueue); // 打印队列
//     }

//     return 0;
// }
void *producer(void *arg)
{
    shareRes_t *pShareRes = (shareRes_t *)arg;
    while (1)
    {
        pthread_mutex_lock(&pShareRes->mutex);
        while (pShareRes->queue.queueSize >= 10) // 队列满时，等待
        {
            pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
        }
        printf("current queue size: %d\n", pShareRes->queue.queueSize);
        int data = rand() % 100; // 生成随机数
        enQueue(&pShareRes->queue, data);
        printf("enqueue %d\n", data);
        visitQueue(&pShareRes->queue);            // 打印队列
        pthread_cond_broadcast(&pShareRes->cond); // 通知所有等待线程
        pthread_mutex_unlock(&pShareRes->mutex);
        sleep(3);
    }
}

void *consumer(void *arg)
{
    shareRes_t *pShareRes = (shareRes_t *)arg;
    sleep(5);
    while (1)
    {
        pthread_mutex_lock(&pShareRes->mutex);
        while (pShareRes->queue.queueSize <= 0) // 队列空时，等待
        {
            pthread_cond_wait(&pShareRes->cond, &pShareRes->mutex);
        }
        printf("current queue size: %d\n", pShareRes->queue.queueSize);
        int head = pShareRes->queue.pHead->data;
        deQueue(&pShareRes->queue);
        printf("dequeue %d\n", head);
        visitQueue(&pShareRes->queue);            // 打印队列
        pthread_cond_broadcast(&pShareRes->cond); // 通知所有等待线程
        pthread_mutex_unlock(&pShareRes->mutex);
        sleep(1);
    }
}

/*单元测试--生产者消费者模型*/
int main(int argc, char *argv[])
{
    shareRes_t shareRes;
    memset(&shareRes.queue, 0, sizeof(shareRes_t)); // 初始化共享资源
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_cond_init(&shareRes.cond, NULL);

    // 初始商品为8
    for (int i = 1; i <= 8; i++)
    {
        int data = rand() % 100; // 生成随机数
        enQueue(&shareRes.queue, data);
        printf("enqueue %d\n", data);
        visitQueue(&shareRes.queue); // 打印队列
    }
    printf("--------------------------\n");

    pthread_t producerTid1, producerTid2, producerTid3, consumerTid1, consumerTid2;

    pthread_create(&producerTid1, NULL, producer, &shareRes);
    pthread_create(&producerTid2, NULL, producer, &shareRes);
    pthread_create(&producerTid3, NULL, producer, &shareRes);
    pthread_create(&consumerTid1, NULL, consumer, &shareRes);
    pthread_create(&consumerTid2, NULL, consumer, &shareRes);

    pthread_join(producerTid1, NULL);
    pthread_join(producerTid2, NULL);
    pthread_join(producerTid3, NULL);
    pthread_join(consumerTid1, NULL);
    pthread_join(consumerTid2, NULL);

    pthread_mutex_destroy(&shareRes.mutex);
    pthread_cond_destroy(&shareRes.cond);

    return 0;
}