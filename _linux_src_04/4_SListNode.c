
#include "SList.h"

// 打印
void SListPrint(SListNode *phead)
{
    SListNode *cur = phead;
    while (cur)
    {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

// 申请新结点
SListNode *SListBuyNode(SLTDataType x)
{
    SListNode *node = (SListNode *)malloc(sizeof(SListNode));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->data = x;
    node->next = NULL;
    return node;
}

// 尾插
void SListPushBack(SListNode **pphead, SLTDataType x)
{
    assert(pphead);
    SListNode *newnode = SListBuyNode(x);

    if (*pphead == NULL)          // 空链表
    {
        *pphead = newnode;
    }
    else
    {
        SListNode *tail = *pphead;
        while (tail->next)
            tail = tail->next;
        tail->next = newnode;
    }
}

// 头插
void SListPushFront(SListNode **pphead, SLTDataType x)
{
    assert(pphead);
    SListNode *newnode = SListBuyNode(x);
    newnode->next = *pphead;
    *pphead = newnode;
}

// 尾删
void SListPopBack(SListNode **pphead)
{
    assert(pphead && *pphead);
    if ((*pphead)->next == NULL)  // 只有一个结点
    {
        free(*pphead);
        *pphead = NULL;
    }
    else
    {
        SListNode *prev = NULL, *tail = *pphead;
        while (tail->next)
        {
            prev = tail;
            tail = tail->next;
        }
        free(tail);
        prev->next = NULL;
    }
}

// 头删
void SListPopFront(SListNode **pphead)
{
    assert(pphead && *pphead);
    SListNode *next = (*pphead)->next;
    free(*pphead);
    *pphead = next;
}

// 查找
SListNode *SListFind(SListNode *phead, SLTDataType x)
{
    SListNode *cur = phead;
    while (cur)
    {
        if (cur->data == x)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

// 在 pos 位置之后插入
void SListInsert(SListNode **pphead, SListNode *pos, SLTDataType x)
{
    assert(pphead && pos);
    SListNode *newnode = SListBuyNode(x);
    newnode->next = pos->next;
    pos->next = newnode;
}

// 删除 pos 位置之后的结点
void SListErase(SListNode **pphead, SListNode *pos)
{
    assert(pphead && pos && pos->next);
    SListNode *del = pos->next;
    pos->next = del->next;
    free(del);
}

// 销毁整个链表
void SListDestory(SListNode **pphead)
{
    assert(pphead);
    SListNode *cur = *pphead;
    while (cur)
    {
        SListNode *next = cur->next;
        free(cur);
        cur = next;
    }
    *pphead = NULL;
}


int main(void)
{
    SListNode *plist = NULL;          // 1. 初始化空链表

    // 尾插 1 2 3
    SListPushBack(&plist, 1);
    SListPushBack(&plist, 2);
    SListPushBack(&plist, 3);
    SListPrint(plist);                // 1 -> 2 -> 3 -> NULL

    // 头插 0
    SListPushFront(&plist, 0);
    SListPrint(plist);                // 0 -> 1 -> 2 -> 3 -> NULL

    // 尾删一次
    SListPopBack(&plist);
    SListPrint(plist);                // 0 -> 1 -> 2 -> NULL

    // 查找 1 并在它后面插入 99
    SListNode *pos = SListFind(plist, 1);
    if (pos)
        SListInsert(&plist, pos, 99);
    SListPrint(plist);                // 0 -> 1 -> 99 -> 2 -> NULL

    // 销毁
    SListDestory(&plist);
    return 0;
}