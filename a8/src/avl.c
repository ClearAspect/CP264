
#include "avl.h"
#include <stdlib.h>
#include <string.h>

// Helper function to create a new node
AVLNODE *new_node(RECORD data) {
	AVLNODE *np = (AVLNODE *)malloc(sizeof(AVLNODE));
	if (np == NULL)
		return NULL;
	np->data = data;
	np->height = 1;
	np->left = NULL;
	np->right = NULL;
	return np;
}

void avl_insert(AVLNODE **rootp, RECORD data) {
	// Standard BST insertion
	if (*rootp == NULL) {
		*rootp = new_node(data);
		return;
	}

	// Compare names for insertion direction
	int cmp = strcmp(data.name, (*rootp)->data.name);

	if (cmp < 0)
		avl_insert(&(*rootp)->left, data);
	else if (cmp > 0)
		avl_insert(&(*rootp)->right, data);
	else
		return; // Duplicate name, no insertion

	// Update height of this ancestor node
	(*rootp)->height = 1 + ((height((*rootp)->left) > height((*rootp)->right))
															? height((*rootp)->left)
															: height((*rootp)->right));

	// Get the balance factor to check if this node became unbalanced
	int balance = balance_factor(*rootp);

	// Left Left Case
	if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) < 0) {
		*rootp = rotate_right(*rootp);
		return;
	}

	// Right Right Case
	if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) > 0) {
		*rootp = rotate_left(*rootp);
		return;
	}

	// Left Right Case
	if (balance > 1 && strcmp(data.name, (*rootp)->left->data.name) > 0) {
		(*rootp)->left = rotate_left((*rootp)->left);
		*rootp = rotate_right(*rootp);
		return;
	}

	// Right Left Case
	if (balance < -1 && strcmp(data.name, (*rootp)->right->data.name) < 0) {
		(*rootp)->right = rotate_right((*rootp)->right);
		*rootp = rotate_left(*rootp);
		return;
	}
}

void avl_delete(AVLNODE **rootp, char *key) {
	// Standard BST delete
	if (*rootp == NULL)
		return;

	// Search for the node to be deleted
	if (strcmp(key, (*rootp)->data.name) < 0)
		avl_delete(&(*rootp)->left, key);
	else if (strcmp(key, (*rootp)->data.name) > 0)
		avl_delete(&(*rootp)->right, key);
	else { // Found node to delete
		// Node with only one child or no child
		if ((*rootp)->left == NULL) {
			AVLNODE *temp = (*rootp)->right;
			free(*rootp);
			*rootp = temp;
		} else if ((*rootp)->right == NULL) {
			AVLNODE *temp = (*rootp)->left;
			free(*rootp);
			*rootp = temp;
		} else { // Node with two children
			// Get the inorder successor (smallest in the right subtree)
			AVLNODE *temp = find_min_node((*rootp)->right);

			// Copy the inorder successor's data to this node
			(*rootp)->data = temp->data;

			// Delete the inorder successor
			avl_delete(&(*rootp)->right, temp->data.name);
		}
	}

	// If the tree had only one node then return
	if (*rootp == NULL)
		return;

	// Update height of current node
	(*rootp)->height = 1 + ((height((*rootp)->left) > height((*rootp)->right))
															? height((*rootp)->left)
															: height((*rootp)->right));

	// Check balance factor to see if rebalancing is needed
	int balance = balance_factor(*rootp);

	// Left Left Case
	if (balance > 1 && balance_factor((*rootp)->left) >= 0) {
		*rootp = rotate_right(*rootp);
		return;
	}

	// Left Right Case
	if (balance > 1 && balance_factor((*rootp)->left) < 0) {
		(*rootp)->left = rotate_left((*rootp)->left);
		*rootp = rotate_right(*rootp);
		return;
	}

	// Right Right Case
	if (balance < -1 && balance_factor((*rootp)->right) <= 0) {
		*rootp = rotate_left(*rootp);
		return;
	}

	// Right Left Case
	if (balance < -1 && balance_factor((*rootp)->right) > 0) {
		(*rootp)->right = rotate_right((*rootp)->right);
		*rootp = rotate_left(*rootp);
		return;
	}
}

AVLNODE *avl_search(AVLNODE *root, char *key) {
	if (root == NULL || strcmp(key, root->data.name) == 0)
		return root;

	if (strcmp(key, root->data.name) < 0)
		return avl_search(root->left, key);

	return avl_search(root->right, key);
}

// Find the node with minimum value in a tree
AVLNODE *find_min_node(AVLNODE *node) {
	AVLNODE *current = node;

	// Find the leftmost leaf
	while (current->left != NULL)
		current = current->left;

	return current;
}

int height(AVLNODE *root) {

	if (root == NULL)
		return 0;
	return root->height;
}

int balance_factor(AVLNODE *np) {

	if (np == NULL)
		return 0;
	return height(np->left) - height(np->right);
}

AVLNODE *rotate_left(AVLNODE *np) {

	AVLNODE *new_root = np->right;
	AVLNODE *subtree = new_root->left;

	// Perform rotation
	new_root->left = np;
	np->right = subtree;

	// Update heights
	np->height = 1 + ((height(np->left) > height(np->right)) ? height(np->left)
																													 : height(np->right));
	new_root->height = 1 + ((height(new_root->left) > height(new_root->right))
															? height(new_root->left)
															: height(new_root->right));

	// Return new root
	return new_root;
}

AVLNODE *rotate_right(AVLNODE *np) {

	AVLNODE *new_root = np->left;
	AVLNODE *subtree = new_root->right;

	// Perform rotation
	new_root->right = np;
	np->left = subtree;

	// Update heights
	np->height = 1 + ((height(np->left) > height(np->right)) ? height(np->left)
																													 : height(np->right));
	new_root->height = 1 + ((height(new_root->left) > height(new_root->right))
															? height(new_root->left)
															: height(new_root->right));

	// Return new root
	return new_root;
}

// Clean up the AVL tree by freeing all nodes
void avl_clean(AVLNODE **rootp) {
	if (*rootp == NULL)
		return;

	// Post-order traversal to delete all nodes
	avl_clean(&(*rootp)->left);
	avl_clean(&(*rootp)->right);

	free(*rootp);
	*rootp = NULL;
}
