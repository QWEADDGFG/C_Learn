#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "List.h"

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/
// 单元测试
int main(void) {
	List* list = list_create();

	// add_before_head(list, 1);
	// add_before_head(list, 2);
	// add_before_head(list, 3);
	// add_before_head(list, 4);	// 4 --> 3 --> 2 --> 1

	add_hehind_tail(list, 1);
	add_hehind_tail(list, 2);
	add_hehind_tail(list, 3);
	add_hehind_tail(list, 4);	// 1 --> 2 --> 3 --> 4

	// add_node(list, 0, 100);
	// add_node(list, 3, 200);
	// add_node(list, 6, 300);		// 100 -> 1 -> 2 -> 200 -> 3 -> 4 -> 300
	// add_node(list, 10, 400);

	// delete_node(list, 3);
	// delete_node(list, 1);
	// delete_node(list, 10);

	Node* node1 = find_by_index(list, 2);
	Node* node2 = find_by_index(list, 10);
	return 0;
}