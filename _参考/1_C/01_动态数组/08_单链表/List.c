#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// API
List* list_create(void) {
	return calloc(1, sizeof(List));
}

void list_destroy(List* list) {
	// 1. 释放所有结点
	Node* curr = list->head;
	while (curr) {
		Node* next = curr->next;
		free(curr);
		curr = next;
	} // curr == NULL
	// 2. 释放List结构体
	free(list);
}

// 头插法
void add_before_head(List* list, E val) {
	// 1. 创建新结点
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) {
		printf("Error: malloc failed in add_before_head\n");
		exit(1);
	}
	// 2. 初始化结点
	new_node->data = val;
	new_node->next = list->head;
	// 3. 更新链表的信息
	list->head = new_node;
	if (list->tail == NULL) {
		list->tail = new_node;
	}
	list->size++;
}

// 尾插法
void add_hehind_tail(List* list, E val) {
	// 1. 创建新结点
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) {
		printf("Error: malloc failed in add_before_head\n");
		exit(1);
	}
	// 2. 初始化结点
	new_node->data = val;
	new_node->next = NULL;
	// 3. 链接并修改更新链表的信息
	if (list->tail == NULL) {
		list->head = new_node;
		list->tail = new_node;
	} else {
		list->tail->next = new_node;
		list->tail = new_node;
	}
	list->size++;
}

void add_node(List* list, int idx, E val) {
	// 参数校验
	if (idx < 0 || idx > list->size) {
		printf("Illegal Argument: idx = %d, size = %d\n", idx, list->size);
		exit(1);
	}
	if (idx == 0) {
		add_before_head(list, val);
		return;
	}
	if (idx == list->size) {
		add_hehind_tail(list, val);
		return;
	}
	// 在链表的中间插入
	// 找索引为 idx-1 的结点
	// 循环不变式：curr和i是对应的
	Node* curr = list->head;
	for (int i = 0; i < idx - 1; i++) {
		curr = curr->next;
	} 
	// 在curr的后面添加结点
	// 1. 创建新结点
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) {
		printf("Error: malloc failed in add_before_head\n");
		exit(1);
	}
	// 2. 初始化结点
	new_node->data = val;
	new_node->next = curr->next;
	// 3. 链接
	curr->next = new_node;
	// 4. 修改链表的信息
	list->size++;
}

// 删除第一个值与val相等的结点
void delete_node(List* list, E val) {
	Node* prev = NULL;
	Node* curr = list->head;
	
	// 找到第一个值与val相等的结点
	while (curr) {
		if (curr->data == val) {
			// 删除curr结点
			if (prev == NULL) {
				// 删除第一个结点
				list->head = curr->next;
				if (list->tail == curr) {
					list->tail = NULL;
				}
			} else {
				prev->next = curr->next;
				if (list->tail == curr) {
					list->tail = prev;
				}
			}
			list->size--;
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	} // curr == NULL
}

// 查找第一个与指定值相等的结点
Node* search_for_value(List* list, E val) {
	Node* curr = list->head;
	while (curr) {
		if (curr->data == val) {
			return curr;
		}
		curr = curr->next;
	} // curr == NULL
	return NULL;
}

// 根据索引查找值
Node* find_by_index(List* list, int idx) {
	// 参数校验
	if (idx < 0 || idx >= list->size) {
		printf("Illegal Argument: idx=%d, size=%d\n", idx, list->size);
		exit(1);
	}
	// 循环不变式：curr指向结点的索引为i
	Node* curr = list->head;
	for (int i = 0; i < idx; i++) {
		curr = curr->next;
	} // i == idx
	return curr;
}