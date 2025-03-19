#include "tree.h"
#include "queue_stack.h"
#include <stdio.h>
#include <stdlib.h>

TPROPS tree_property(TNODE *root) {
	TPROPS props = {0, 0};
	if (root == NULL)
		return props;

	// Calculate left and right subtree properties
	TPROPS left_props = tree_property(root->left);
	TPROPS right_props = tree_property(root->right);

	// Total order is current node + left subtree + right subtree
	props.order = 1 + left_props.order + right_props.order;

	// Height is the max of left and right subtree heights + 1
	props.height =
			1 + (left_props.height > right_props.height ? left_props.height
																									: right_props.height);

	return props;
}

void preorder(TNODE *root) {
	if (root) {
		printf("%c ", root->data); // Process current node first
		preorder(root->left);			 // Process left subtree
		preorder(root->right);		 // Process right subtree
	}
}

void inorder(TNODE *root) {
	if (root) {
		inorder(root->left);			// Process left subtree
		printf("%c", root->data); // Process current node
		inorder(root->right);			// Process right subtree
	}
}

void postorder(TNODE *root) {
	if (root) {
		postorder(root->left);		 // Process left subtree
		postorder(root->right);		 // Process right subtree
		printf("%c ", root->data); // Process current node
	}
}

void bforder(TNODE *root) {
	if (root == NULL)
		return;

	QUEUE queue = {0};
	enqueue(&queue, root);

	while (queue.front != NULL) {
		TNODE *node = (TNODE *)dequeue(&queue);
		printf("%c ", node->data);

		// Add left child to queue
		if (node->left)
			enqueue(&queue, node->left);

		// Add right child to queue
		if (node->right)
			enqueue(&queue, node->right);
	}

	clean_queue(&queue);
}

TNODE *bfs(TNODE *root, char key) {
	if (root == NULL)
		return NULL;

	QUEUE queue = {0};
	enqueue(&queue, root);

	while (queue.front != NULL) {
		TNODE *node = (TNODE *)dequeue(&queue);

		// Check if current node is the one we're looking for
		if (node->data == key) {
			clean_queue(&queue);
			return node;
		}

		// Add left child to queue
		if (node->left)
			enqueue(&queue, node->left);

		// Add right child to queue
		if (node->right)
			enqueue(&queue, node->right);
	}

	clean_queue(&queue);
	return NULL; // Key not found
}

TNODE *dfs(TNODE *root, char key) {
	if (root == NULL)
		return NULL;

	STACK stack = {0};
	push(&stack, root);

	while (stack.top != NULL) {
		TNODE *node = (TNODE *)pop(&stack);

		// Check if current node is the one we're looking for
		if (node->data == key) {
			clean_stack(&stack);
			return node;
		}

		// Push right child first (so that left child is processed first)
		if (node->right)
			push(&stack, node->right);

		// Push left child
		if (node->left)
			push(&stack, node->left);
	}

	clean_stack(&stack);
	return NULL; // Key not found
}

TNODE *tree_node(char val) {
	TNODE *np = (TNODE *)malloc(sizeof(TNODE));
	if (np != NULL) {
		np->data = val;
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

void clean_tree(TNODE **rootp) {
	TNODE *root = *rootp;
	if (root) {
		clean_tree(&root->left);
		clean_tree(&root->right);
		free(root);
		*rootp = NULL;
	}
}

void insert_tree(TNODE **rootp, char val) {
	if (*rootp == NULL) {
		*rootp = tree_node(val);
		return;
	}

	QUEUE queue = {0};
	enqueue(&queue, *rootp);

	while (queue.front != NULL) {
		TNODE *node = (TNODE *)dequeue(&queue);

		// If left child is NULL, add new node as left child
		if (node->left == NULL) {
			node->left = tree_node(val);
			break;
		} else {
			enqueue(&queue, node->left);
		}

		// If right child is NULL, add new node as right child
		if (node->right == NULL) {
			node->right = tree_node(val);
			break;
		} else {
			enqueue(&queue, node->right);
		}
	}

	clean_queue(&queue);
}
