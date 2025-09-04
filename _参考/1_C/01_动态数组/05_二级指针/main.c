#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
 // one pass
typedef struct node {
	int data;
	struct node* next;
} Node;

void addNode(Node** phead, int data) {
	// 1. 创建结点
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) {
		printf("Error: malloc failed in addNode.\n");
		exit(1);
	}
	// 2. 初始化结点
	new_node->data = data;
	new_node->next = *phead;

	*phead = new_node;
}

int main(void) {
	Node* head = NULL;	// 空链表
	addNode(&head, 1);
	addNode(&head, 2);
	addNode(&head, 3);
	addNode(&head, 4);	// 4 --> 3 --> 2 --> 1

	return 0;
}