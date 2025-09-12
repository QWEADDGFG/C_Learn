#include "func.h"

//

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

int main(int argc, char *argv[])
{
    queue_t myQueue;
    memset(&myQueue, 0, sizeof(queue_t));//初始化队列
    for (int i = 1; i <= 5; i++)
    {
        int data = rand() % 100; // 生成随机数
        enQueue(&myQueue, data);
    }
    visitQueue(&myQueue); // 打印队列
    deQueue(&myQueue); // 出队
    visitQueue(&myQueue); // 打印队列
    deQueue(&myQueue); // 出队
    visitQueue(&myQueue); // 打印队列
    deQueue(&myQueue); // 出队
    visitQueue(&myQueue); // 打印队列


    return 0;
}