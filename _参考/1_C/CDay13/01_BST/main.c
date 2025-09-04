#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "BST.h"

/**********************************************************************
 *                          COMMENT                                   *
 **********************************************************************/

int main(void) {
	BST* tree = bst_create();

	bst_insert(tree, 9);
	bst_insert(tree, 42);
	bst_insert(tree, 57);
	bst_insert(tree, 5);
	bst_insert(tree, 3);
	bst_insert(tree, 13);

	// TreeNode* node1 = bst_search(tree, 42);
	// TreeNode* node2 = bst_search(tree, 9527);

	// bst_delete(tree, 3);
	// bst_delete(tree, 5);
	bst_delete(tree, 9);

	// 中序遍历
	// bst_inorder(tree);
	// 
	// 层次遍历
	// bst_levelorder(tree);
	return 0;
}