#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

/* 链表结点 */
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

/* 带头尾指针的单向链表管理结构（使用虚拟头结点） */
typedef struct LinkedList{
    ListNode *head; /* 指向虚拟头结点 */
    ListNode *tail; /* 指向真实尾结点（为空时等于 head） */
    size_t size;    /* 有效结点数量（不计虚拟头结点） */
} LinkedList;

/* 函数声明 */
LinkedList* list_create(void);
void        list_destroy(LinkedList *list);
bool        list_push_back(LinkedList *list, int value);
bool        list_push_front(LinkedList *list, int value);
bool        list_remove_once(LinkedList *list, int value);
bool        list_remove_all(LinkedList *list, int value);
bool        list_remove_at(LinkedList *list, size_t index);
bool        list_get(LinkedList *list, size_t index, int *out);
void        list_print(LinkedList *list);

/*
   实现部分（可选）：在一个源文件中在包含本头文件之前 #define LIST_IMPL
   例如：
     #define LIST_IMPL
     #include "linked_list.h"
   这样会生成函数实现；其它源文件只需 #include "linked_list.h" 不用定义 LIST_IMPL。
*/
#ifdef LIST_IMPL

LinkedList* list_create(void) {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) return NULL;
    ListNode *dummy = (ListNode*)malloc(sizeof(ListNode));
    if (!dummy) { free(list); return NULL; }
    dummy->next = NULL;
    list->head = dummy;
    list->tail = dummy;
    list->size = 0;
    return list;
}

void list_destroy(LinkedList *list) {
    if (!list) return;
    ListNode *p = list->head;
    while (p) {
        ListNode *next = p->next;
        free(p);
        p = next;
    }
    free(list);
}

bool list_push_back(LinkedList *list, int value) {
    if (!list) return false;
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return false;
    node->data = value;
    node->next = NULL;
    list->tail->next = node;
    list->tail = node;
    list->size++;
    return true;
}

bool list_push_front(LinkedList *list, int value) {
    if (!list) return false;
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return false;
    node->data = value;
    node->next = list->head->next;
    list->head->next = node;
    if (list->tail == list->head) list->tail = node;
    list->size++;
    return true;
}

bool list_remove_once(LinkedList *list, int value) {
    if (!list || list->size == 0) return false;
    ListNode *prev = list->head;
    ListNode *cur = prev->next;
    while (cur) {
        if (cur->data == value) {
            prev->next = cur->next;
            if (cur == list->tail) list->tail = prev;
            free(cur);
            list->size--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

bool list_remove_all(LinkedList *list, int value) {
    if (!list || list->size == 0) return false;

    ListNode *prev = list->head;
    ListNode *cur  = prev->next;
    bool removed = false;

    while (cur) {
        if (cur->data == value) {
            ListNode *next = cur->next;
            prev->next = next;
            if (cur == list->tail) list->tail = prev;
            free(cur);
            list->size--;
            removed = true;
            cur = next;
        } else {
            prev = cur;
            cur  = cur->next;
        }
    }
    return removed;
}

bool list_remove_at(LinkedList *list, size_t index) {
    if (!list || index >= list->size) return false;
    ListNode *prev = list->head;
    for (size_t i = 0; i < index; ++i) prev = prev->next;
    ListNode *cur = prev->next;
    prev->next = cur->next;
    if (cur == list->tail) list->tail = prev;
    free(cur);
    list->size--;
    return true;
}

bool list_get(LinkedList *list, size_t index, int *out) {
    if (!list || index >= list->size || !out) return false;
    ListNode *p = list->head->next;
    for (size_t i = 0; i < index; ++i) p = p->next;
    *out = p->data;
    return true;
}

void list_print(LinkedList *list) {
    if (!list) {
        printf("NULL list\n");
        return;
    }
    printf("size=%zu: ", list->size);
    ListNode *p = list->head->next;
    while (p) {
        printf("%d -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

#endif /* LIST_IMPL */

#endif /* LINKED_LIST_H */