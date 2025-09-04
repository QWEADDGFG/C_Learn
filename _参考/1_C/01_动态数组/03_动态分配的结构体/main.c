#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
 // one pass
typedef struct node{
	int data;
	struct node* next;
} Node;

Node* addNode(Node* head, int data) {
	// 1. 创建结点
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) {
		printf("Error: malloc failed in addNode.\n");
		exit(1);
	}
	// 2. 初始化结点
	new_node->data = data;
	new_node->next = head;

	head = new_node;
	return head;
}

int main(void) {
	Node* head = NULL;	// 空链表
	head = addNode(head, 1);
	head = addNode(head, 2);
	head = addNode(head, 3);
	head = addNode(head, 4);	// 4 --> 3 --> 2 --> 1

	return 0;
}