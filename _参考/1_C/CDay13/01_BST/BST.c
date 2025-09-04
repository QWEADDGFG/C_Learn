#include "BST.h"
#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

// 创建一颗空树
BST* bst_create(void) {
	return calloc(1, sizeof(BST));
}

// a. 如果 key 存在，什么也不做
// b. 如果 key 不存在，则添加 key
void bst_insert(BST* tree, K key) {
	TreeNode* parent = NULL;
	TreeNode* curr = tree->root;
	int cmp;
	while (curr) {
		// 带选择的单链表
		cmp = key - curr->key;

		if (cmp < 0) {
			parent = curr;
			curr = curr->left;
		} else if (cmp > 0) {
			parent = curr;
			curr = curr->right;
		} else {
			return;
		}
	} // curr == NULL;

	// 创建结点
	TreeNode* node = calloc(1, sizeof(TreeNode));
	// 初始化结点
	node->key = key;
	// 链接
	if (parent == NULL) {
		tree->root = node;
	} else if (cmp < 0) {
		parent->left = node;
	} else {
		parent->right = node;
	}
}

TreeNode* bst_search(BST* tree, K key) {
	TreeNode* curr = tree->root;
	while (curr) {
		int cmp = key - curr->key;

		if (cmp < 0) {
			curr = curr->left;
		} else if (cmp > 0) {
			curr = curr->right;
		} else {
			return curr;
		}
	} // curr == NULL
	return NULL;
}

void bst_delete(BST* tree, K key) {
	// 1. 查找要删除的结点
	TreeNode* parent = NULL;
	TreeNode* curr = tree->root;
	while (curr) {
		int cmp = key - curr->key;

		if (cmp < 0) {
			parent = curr;
			curr = curr->left;
		} else if (cmp > 0) {
			parent = curr;
			curr = curr->right;
		} else {
			// 代码缩进的层次越高，代码的复杂度就越高，可读性越差。
			break;
		}
	} // curr == NULL || curr != NULL

	if (curr == NULL) return;
	// 2. 删除curr结点
	// 先处理 degree == 2 的情况
	if (curr->left && curr->right) {
		// 退化成 degree == 0 || degree == 1
		TreeNode* p = curr;
		TreeNode* min = curr->right;
		while (min->left) {
			p = min;
			min = min->left;
		}	// min->left == NULL

		curr->key = min->key;
		parent = p;
		curr = min;
	}
	// 统一处理 (degree == 0 || degree == 1)
	TreeNode* child = curr->left ? curr->left : curr->right; // 找到唯一的孩子

	if (parent == NULL) {
		tree->root = child;
	} else {
		// 必须重新比较，因为可能发生了退化
		int cmp = curr->key - parent->key;
		if (cmp < 0) {
			parent->left = child;
		} else if (cmp > 0) {
			parent->right = child;
		} else { // Caution: 可能 cmp == 0
			parent->right = child;
		}
	}
	free(curr);
}

/**********************************************************/
/*                     中序遍历                            */
/**********************************************************/
// 内部的实现细节
void inorder(TreeNode* root) {
	// a. 边界条件
	if (root == NULL) {
		return;
	}
	// b. 递归公式
	// 遍历左子树
	inorder(root->left);
	// 遍历根结点
	printf("%d ", root->key);
	// 遍历右子树
	inorder(root->right);
}

// 对外的API
void bst_inorder(BST* tree) {
	// 委托 (外包)
	inorder(tree->root);
	printf("\n");
}

/**********************************************************/
/*                     层次遍历                            */
/**********************************************************/
void bst_levelorder(BST* tree) {
	// 1. 创建队列
	Queue* q = queue_create();
	// 2. 将根结点入队列
	queue_push(q, tree->root);
	// 3. 遍历
	while (!queue_empty(q)) {
		// 出队列
		TreeNode* node = queue_pop(q);
		// 遍历该结点
		printf("%d ", node->key);
		// 判断该结点是否有左孩子
		if (node->left) {
			queue_push(q, node->left);
		}
		if (node->right) {
			queue_push(q, node->right);
		}
	} // queue_empty(q) == true
	printf("\n");
}