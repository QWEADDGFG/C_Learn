#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

/* 节点结构（数据为 int，可按需替换为 struct 或 void*） */
typedef struct Node
{
    int val;
    struct Node *next;
} Node;

/* 循环单链表结构，含虚拟头节点 dummy，及尾指针 tail */
typedef struct CLinkedList
{
    Node *dummy; /* 虚拟头节点 */
    Node *tail;  /* 指向最后一个真实节点；当链表为空时，tail == dummy */
    size_t size; /* 真实节点个数 */
} CLinkedList;

/* 创建并初始化空链表，返回指针（失败返回 NULL） */
CLinkedList *clist_create(void)
{
    CLinkedList *list = (CLinkedList *)malloc(sizeof(CLinkedList));
    if (!list)
        return NULL;
    Node *d = (Node *)malloc(sizeof(Node));
    if (!d)
    {
        free(list);
        return NULL;
    }
    d->next = d; /* 空表时 dummy 指向自己，保持循环 */
    list->dummy = d;
    list->tail = d; /* 空表 tail 指向 dummy */
    list->size = 0;
    return list;
}

/* 销毁链表并释放内存 */
void clist_destroy(CLinkedList *list)
{
    if (!list)
        return;
    Node *d = list->dummy;
    if (d)
    {
        Node *cur = d->next;
        while (cur != d)
        {
            Node *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        free(d);
    }
    free(list);
}

/* 在位置 pos 插入值 val
   pos 的范围是 [0, size]，0 表示插入到第一个位置（头部）
   返回 0 成功，非0 表示失败（如内存分配失败或 pos 越界） */
int clist_insert(CLinkedList *list, size_t pos, int val)
{
    if (!list)
        return -1;
    if (pos > list->size)
        return -2; /* 越界 */
    Node *prev = list->dummy;
    /* 找到插入位置的前一个节点 prev（从 dummy 开始，移动 pos 步） */
    for (size_t i = 0; i < pos; ++i)
        prev = prev->next;
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node)
        return -3;
    node->val = val;
    node->next = prev->next;
    prev->next = node;
    /* 如果插入到末尾（pos == size），需要更新 tail */
    if (pos == list->size)
    {
        list->tail = node;
    }
    list->size++;
    return 0;
}

/* 在链表尾部插入 */
int clist_push_back(CLinkedList *list, int val)
{
    return clist_insert(list, list ? list->size : 0, val);
}

/* 在链表头部插入 */
int clist_push_front(CLinkedList *list, int val)
{
    return clist_insert(list, 0, val);
}

/* 删除位置 pos 的节点，pos 范围 [0, size-1]
   out_val 可选，不为 NULL 时将被赋值为被删除节点的值
   返回 0 成功，非0 失败（如越界） */
int clist_remove(CLinkedList *list, size_t pos, int *out_val)
{
    if (!list)
        return -1;
    if (list->size == 0)
        return -2; /* 空表 */
    if (pos >= list->size)
        return -3; /* 越界 */
    Node *prev = list->dummy;
    for (size_t i = 0; i < pos; ++i)
        prev = prev->next;
    Node *target = prev->next;
    prev->next = target->next;
    if (out_val)
        *out_val = target->val;
    /* 如果删除的是 tail，需要更新 tail（如果删除后表为空，tail 指向 dummy） */
    if (target == list->tail)
    {
        if (prev == list->dummy && prev->next == prev)
        {
            /* 删除后空表 */
            list->tail = list->dummy;
        }
        else
        {
            list->tail = prev;
        }
    }
    free(target);
    list->size--;
    return 0;
}

/* 删除头部 */
int clist_pop_front(CLinkedList *list, int *out_val)
{
    return clist_remove(list, 0, out_val);
}

/* 删除尾部 */
int clist_pop_back(CLinkedList *list, int *out_val)
{
    if (!list)
        return -1;
    if (list->size == 0)
        return -2;
    /* tail 指向最后一个真实节点，需找到尾节点的前驱 prev
       可以用循环或利用 size 来从 dummy 移动 size-1 步到 prev */
    Node *prev = list->dummy;
    for (size_t i = 0; i < list->size - 1; ++i)
        prev = prev->next;
    /* prev 是尾节点的前驱（如果 size==1，则 prev == dummy） */
    return clist_remove(list, list->size - 1, out_val);
}

/* 根据位置获取节点值（不删除）
   pos 范围 [0, size-1]，out_val 非 NULL 用于返回值
   返回 0 成功，非0 失败 */
int clist_get(CLinkedList *list, size_t pos, int *out_val)
{
    if (!list)
        return -1;
    if (list->size == 0)
        return -2;
    if (pos >= list->size)
        return -3;
    Node *cur = list->dummy->next;
    for (size_t i = 0; i < pos; ++i)
        cur = cur->next;
    if (out_val)
        *out_val = cur->val;
    return 0;
}

/* 根据位置更新节点值
   返回 0 成功，非0 失败 */
int clist_set(CLinkedList *list, size_t pos, int val)
{
    if (!list)
        return -1;
    if (list->size == 0)
        return -2;
    if (pos >= list->size)
        return -3;
    Node *cur = list->dummy->next;
    for (size_t i = 0; i < pos; ++i)
        cur = cur->next;
    cur->val = val;
    return 0;
}

/* 查找第一个值为 val 的节点，返回其位置（0-based），未找到返回 -1 */
ssize_t clist_find(CLinkedList *list, int val)
{
    if (!list)
        return -1;
    Node *d = list->dummy;
    Node *cur = d->next;
    ssize_t idx = 0;
    while (cur != d)
    {
        if (cur->val == val)
            return idx;
        cur = cur->next;
        idx++;
    }
    return -1;
}

/* 遍历并打印链表（用于调试） */
void clist_print(CLinkedList *list)
{
    if (!list)
    {
        printf("(null list)\n");
        return;
    }
    Node *d = list->dummy;
    Node *cur = d->next;
    printf("size=%zu: [", list->size);
    int first = 1;
    while (cur != d)
    {
        if (!first)
            printf(", ");
        printf("%d", cur->val);
        first = 0;
        cur = cur->next;
    }
    printf("]\n");
}

/* 示例使用 : 步长为 3 的约瑟夫问题*/
int main(void)
{
    CLinkedList *list = clist_create();
    if (!list)
    {
        fprintf(stderr, "create failed\n");
        return 1;
    }
    for (int i = 1; i < 42; i++)
    {
        clist_push_back(list, i);
    }
    clist_print(list);
    int k = 3;
    long curr = 0; // 从第0个元素开始计数
    while (list->size > 2) {
        long del = (curr + k - 1) % list->size;
        printf("removing index %ld (size=%ld)\n", del, list->size);
        clist_remove(list, del, NULL);
        if (list->size > 0)
            curr = del % list->size; // 下一轮从被删节点的下一个位置开始计数（索引仍为 del）
    }
    clist_print(list);
    clist_destroy(list);
    return 0;
}