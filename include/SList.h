#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int SLTDataType;

typedef struct SListNode
{
    SLTDataType data;
    struct SListNode *next; // 存放下一个结点的地址

} SListNode;

// 打印链表
void SListPrint(SListNode *phead);

// 申请结点
SListNode *SListBuyNode(SLTDataType x);

// 因为我们是通过一个指针指向该链表的头结点，同时因为在进行插入删除操作时可能改变链表的头结点，所下面的参数需传二级指针
// 尾插
void SListPushBack(SListNode **pphead, SLTDataType x);

// 头插
void SListPushFront(SListNode **pphead, SLTDataType x);

// 尾删
void SListPopBack(SListNode **pphead);

// 头删
void SListPopFront(SListNode **pphead);

// 查找
SListNode *SListFind(SListNode *phead, SLTDataType x);

// 指定位置后面插入
void SListInsert(SListNode **pphead, SListNode *pos, SLTDataType x);

// 指定位置后面删除
void SListErase(SListNode **pphead, SListNode *pos);

// 销毁链表
void SListDestory(SListNode **pphead);