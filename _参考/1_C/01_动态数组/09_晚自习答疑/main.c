#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
struct ListNode {
	int data;
	struct ListNode* next;
};

int middleElement(struct ListNode* head) {
	// 快慢指针
	struct ListNode* fast = head;
	struct ListNode* slow = head;

	while (fast && fast->next) {
		fast = fast->next->next;
		slow = slow->next;
	}	// fast到达末尾：fast == NULL || fast->next == NULL

	return slow->data;
}

int main(void) {
	//struct ListNode* head = malloc(sizeof(struct ListNode));
	//add_before_head(&head, 8);
	//add_before_head(&head, 6);
	//add_before_head(&head, 4);
	//add_before_head(&head, 2); // 2 --> 4 --> 6 --> 8 --> ? --> ....

	struct ListNode node8 = { 8, NULL };
	struct ListNode node6 = { 6, &node8 };
	struct ListNode node4 = { 4, &node6 };
	struct ListNode node2 = { 2, &node4 };	// 2 --> 4 --> 6 --> 8

	printf("middle element: %d\n", middleElement(&node2));

	return 0;
}