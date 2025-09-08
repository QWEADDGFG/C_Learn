#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

/* 创建并初始化空链表（返回已分配的 LinkedList*） */
LinkedList* list_create(void) {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    if (!list) return NULL;
    /* 创建虚拟头结点 */
    ListNode *dummy = (ListNode*)malloc(sizeof(ListNode));
    if (!dummy) { free(list); return NULL; }
    dummy->next = NULL;
    list->head = dummy;
    list->tail = dummy; /* 空表时 tail 指向虚拟头结点 */
    list->size = 0;
    return list;
}

/* 释放链表（释放所有结点和管理结构） */
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

/* 在链表尾部插入一个值（尾插） */
bool list_push_back(LinkedList *list, int value) {
    if (!list) return false;
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return false;
    node->data = value;
    node->next = NULL;
    /* tail 指向最后一个真实结点或虚拟头结点（空表） */
    list->tail->next = node;
    list->tail = node;
    list->size++;
    return true;
}

/* 在链表头部插入一个值（头插，插到第一个真实结点前） */
bool list_push_front(LinkedList *list, int value) {
    if (!list) return false;
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) return false;
    node->data = value;
    node->next = list->head->next;
    list->head->next = node;
    /* 如果原来为空表，则需要更新 tail 指向新节点 */
    if (list->tail == list->head) list->tail = node;
    list->size++;
    return true;
}

/* 删除第一个值等于 value 的结点（若找到并删除返回 true） */
bool list_remove_once(LinkedList *list, int value) {
    if (!list || list->size == 0) return false;
    ListNode *prev = list->head;
    ListNode *cur = prev->next;
    while (cur) {
        if (cur->data == value) {
            prev->next = cur->next;
            /* 如果删除的是尾结点，需要更新 tail 指针 */
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

/* 删除所有值等于 value 的结点，返回是否删过 */
bool list_remove_all(LinkedList *list, int value) {
    if (!list || list->size == 0) return false;

    ListNode *prev = list->head;   // 虚拟头
    ListNode *cur  = prev->next;   // 第一个真实结点
    bool removed = false;          // 记录有没有删过

    while (cur) {
        if (cur->data == value) {
            /* 保存下一个结点，防止 free 后断链 */
            ListNode *next = cur->next;

            /* 把 cur 从链中摘出去 */
            prev->next = next;

            /* 若删的是尾结点，更新 tail */
            if (cur == list->tail) list->tail = prev;

            free(cur);
            list->size--;
            removed = true;   // 标记“删过”

            /* 继续检查下一个，不移动 prev */
            cur = next;
        } else {
            /* 没匹配，双双后移 */
            prev = cur;
            cur  = cur->next;
        }
    }
    return removed;
}
/* 按索引删除（0 基）——删除第 index 个真实结点 */
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

/* 获取第 index 个元素（0 基）。若存在，把值写入 *out 并返回 true */
bool list_get(LinkedList *list, size_t index, int *out) {
    if (!list || index >= list->size || !out) return false;
    ListNode *p = list->head->next;
    for (size_t i = 0; i < index; ++i) p = p->next;
    *out = p->data;
    return true;
}

/* 遍历并打印链表元素（用于调试） */
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

/* 示例用法 */
int main(void) {
    LinkedList *list = list_create();
    if (!list) return 1;
    // 往空表中插入元素
    list_push_back(list, 1);
    list_push_back(list, 2);
    list_push_back(list, 10);
    list_push_back(list, 10);
    list_push_back(list, 10);
    list_push_back(list, 10);
    list_push_back(list, 10);
    list_push_back(list, 20);
    list_push_front(list, 10);
    list_push_front(list, 52);
    list_print(list); // size=10: 52 -> 10 -> 1 -> 2 -> 10 -> 10 -> 10 -> 10 -> 10 -> 20 -> NULL

    list_remove_once(list, 10);
    list_print(list); 

    list_remove_all(list, 10);
    list_print(list); 

    list_remove_at(list, 1);
    list_print(list); 

    // 按索引查找元素数据
    int val;
    int index = 2;
    if (list_get(list, index, &val)) printf("index %d value = %d\n", index, val); 

    list_destroy(list);
    return 0;
}