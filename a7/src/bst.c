
#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BSTNODE *bst_node(RECORD data) {
	BSTNODE *np = (BSTNODE *)malloc(sizeof(BSTNODE));
	if (np) {
		np->data = data;
		np->left = NULL;
		np->right = NULL;
	}
	return np;
}

BSTNODE *bst_search(BSTNODE *root, char *key) {
	if (root == NULL || strcmp(root->data.name, key) == 0) {
		return root;
	}

	if (strcmp(key, root->data.name) < 0) {
		return bst_search(root->left, key);
	} else {
		return bst_search(root->right, key);
	}
}

void bst_insert(BSTNODE **rootp, RECORD data) {
	if (*rootp == NULL) {
		*rootp = bst_node(data);
		return;
	}

	BSTNODE *root = *rootp;

	if (strcmp(data.name, root->data.name) < 0) {
		bst_insert(&(root->left), data);
	} else if (strcmp(data.name, root->data.name) > 0) {
		bst_insert(&(root->right), data);
	} else {
		// Replace data if the name already exists
		root->data = data;
	}
}

BSTNODE *extract_smallest_node(BSTNODE **rootp) {
	if (*rootp == NULL)
		return NULL;

	BSTNODE *root = *rootp;
	if (root->left == NULL) {
		// This is the smallest node
		*rootp = root->right;
		root->left = NULL;
		root->right = NULL;
		return root;
	} else {
		// The smallest node is in the left subtree
		return extract_smallest_node(&(root->left));
	}
}

void bst_delete(BSTNODE **rootp, char *key) {
	if (*rootp == NULL)
		return;

	BSTNODE *root = *rootp;

	if (strcmp(key, root->data.name) < 0) {
		bst_delete(&(root->left), key);
	} else if (strcmp(key, root->data.name) > 0) {
		bst_delete(&(root->right), key);
	} else {
		// Found the node to delete

		// Case 1: Node has no children or only one child
		if (root->left == NULL) {
			BSTNODE *temp = root->right;
			free(root);
			*rootp = temp;
			return;
		} else if (root->right == NULL) {
			BSTNODE *temp = root->left;
			free(root);
			*rootp = temp;
			return;
		}

		// Case 2: Node has two children
		// Find the in-order successor (smallest node in right subtree)
		BSTNODE *successor = extract_smallest_node(&(root->right));

		// Replace the node's data with successor's data
		successor->left = root->left;
		successor->right = root->right;
		free(root);
		*rootp = successor;
	}
}

void bst_clean(BSTNODE **rootp) {
	if (*rootp == NULL)
		return;

	BSTNODE *root = *rootp;

	// Post-order traversal to clean the tree
	bst_clean(&(root->left));
	bst_clean(&(root->right));

	// Free the current node
	free(root);
	*rootp = NULL;
}
