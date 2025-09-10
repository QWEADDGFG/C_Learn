#include "func.h"

// 在主线程中创建一个链表，并插入若干节点，将其传递给子线程，在子线程中遍历链表，并打印节点内容。
typedef struct node_s
{
    int data;
    struct node_s *next;
} node_t;

typedef struct list_s
{
    node_t *pHead;
    node_t *pTail;
    size_t size;
} list_t;

void headInsert(node_t **ppHead, node_t **ppTail, int value)
{
    node_t *pNew = (node_t *)calloc(1, sizeof(node_t));
    // calloc分配内存，并初始化为0，其与malloc的区别在于，calloc分配的内存会被初始化为0，而malloc分配的内存不会被初始化。
    if (*ppHead == NULL)
    {
        *ppHead = pNew;
        *ppTail = pNew;
    }
    else
    {
        pNew->next = *ppHead;
        *ppHead = pNew;
    }
    pNew->data = value;
}
void tailInsert(node_t **ppHead, node_t **ppTail, int value)
{
    node_t *pNew = (node_t *)calloc(1, sizeof(node_t));
    if (*ppHead == NULL)
    {
        *ppHead = pNew;
        *ppTail = pNew;
    }
    else
    {
        (*ppTail)->next = pNew;
        *ppTail = pNew;
    }
    pNew->data = value;
}
void printList(node_t *pHead)
{
    node_t *pCur = pHead;
    while (pCur)
    {
        printf("%d ", pCur->data);
        pCur = pCur->next;
    }
    printf("\n");
}

// // 测试main函数
// int main(int argc, char *argv[])
// {
//     node_t *pHead = NULL;
//     node_t *pTail = NULL;
//     for (int i = 0; i < 10; i++)
//     {
//         // headInsert(&pHead, &pTail, i);
//         tailInsert(&pHead, &pTail, i); 
//         printList(pHead);
//     }
//     return 0;
// }

// 在子线程中遍历链表，并打印节点内容。

void *threadFunc(void *arg){
    list_t *pList = (list_t*)arg;
    printf("i am child thread!\n");
    printList(pList->pHead);
    return NULL;
}
int main(int argc, char *argv[])
{   
    list_t list={NULL,NULL,0};
    node_t *pHead = NULL;
    node_t *pTail = NULL;
    for (int i = 0; i < 10; i++)
    {
        tailInsert(&list.pHead, &list.pTail, i);
    }
    pthread_t tid;
    pthread_create(&tid, NULL,threadFunc, &list);
    sleep(1);
    return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>

typedef struct node_s
{
    int data;
    struct node_s *next;
} node_t;

// 头插：在 dummy 之后插入新节点，使其成为第一个数据节点
void headInsert(node_t **ppHead, node_t **ppTail, int value)
{
    node_t *pNew = (node_t *)calloc(1, sizeof(node_t));
    // 插入到 *ppHead（dummy）之后，使新节点成为第一个数据节点
    pNew->next = (*ppHead)->next;
    (*ppHead)->next = pNew;
    // 如果 tail 仍指向 dummy（说明之前没有数据节点），则更新 tail 指向新节点
    if (*ppTail == *ppHead)
    {
        *ppTail = pNew;
    }
    pNew->data = value;
}

// 尾插：在 *ppTail 之后追加新节点，并更新 *ppTail
void tailInsert(node_t **ppHead, node_t **ppTail, int value)
{
    node_t *pNew = (node_t *)calloc(1, sizeof(node_t));
    // 将新节点追加到当前尾节点之后
    (*ppTail)->next = pNew;
    *ppTail = pNew;
    pNew->data = value;
}

// 打印：从 head（dummy）的 next 开始打印实际数据节点
void printList(node_t *head)
{
    node_t *p = head->next; // 跳过虚拟头节点
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 释放链表（包括 dummy）
void freeList(node_t *head)
{
    node_t *p = head;
    while (p)
    {
        node_t *next = p->next;
        free(p);
        p = next;
    }
}

// 测试 main 函数
int main(int argc, char *argv[])
{
    // 创建虚拟头节点 dummy，并让 pHead 和 pTail 指向它
    node_t *pHead = (node_t *)calloc(1, sizeof(node_t)); // dummy
    node_t *pTail = pHead;                               // 初始时 pTail 指向 dummy，表示链表无数据节点

    // 使用 headInsert 和 tailInsert（它们假定存在 dummy）
    headInsert(&pHead, &pTail, 1);
    headInsert(&pHead, &pTail, 2);
    headInsert(&pHead, &pTail, 3);
    headInsert(&pHead, &pTail, 4);
    tailInsert(&pHead, &pTail, 5);
    tailInsert(&pHead, &pTail, 6);
    tailInsert(&pHead, &pTail, 7);
    tailInsert(&pHead, &pTail, 8);

    // 打印实际数据节点
    printList(pHead);

    // 释放所有节点（包括 dummy）
    freeList(pHead);

    return 0;
}
*/