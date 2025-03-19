/**
 * -------------------------------------
 * @file  bst_linked.c
 * Linked BST Source Code File
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "bst_linked.h"

// Macro for comparing node heights
#define MAX_HEIGHT(a, b) ((a) > (b) ? a : b)

//--------------------------------------------------------------------
// Local Functions

/**
 * Initializes a new BST node with a copy of item.
 *
 * @param source pointer to a BST source
 * @param item pointer to the item to assign to the node
 * @return a pointer to a new BST node
 */
static bst_node *bst_node_initialize(const data_ptr item) {
	// Base case: add a new node containing a copy of item.
	bst_node *node = malloc(sizeof *node);
	node->item = malloc(sizeof *node->item);
	data_copy(node->item, item);
	node->height = 1;
	node->left = NULL;
	node->right = NULL;
	return node;
}

/**
 * Helper function to determine the height of node - handles empty node.
 * @param node The node to process.
 * @return The height of the current node.
 */
static int bst_node_height(const bst_node *node) {
	int height = 0;

	if (node != NULL) {
		height = node->height;
	}
	return height;
}

/**
 * Updates the height of a node. Its height is the max of the heights of its
 * child nodes, plus 1.
 * @param node The node to process.
 */
static void bst_update_height(bst_node *node) {
	int left_height = bst_node_height(node->left);
	int right_height = bst_node_height(node->right);

	node->height = MAX_HEIGHT(left_height, right_height) + 1;
	return;
}

/**
 * Inserts item into a BST. Insertion must preserve the BST definition.
 * item may appear only once in source.
 *
 * @param source - pointer to a BST
 * @param node - pointer to a node
 * @param item - the item to insert
 * @return - true if item inserted, false otherwise
 */
static bool bst_insert_aux(bst_linked *source, bst_node **node,
													 const data_ptr item) {
	bool inserted = false;

	if (*node == NULL) {
		// Base case: add a new node containing the item.
		*node = bst_node_initialize(item);
		source->count += 1;
		inserted = true;
	} else {
		// Compare the node data_ptr against the new item.
		int comp = data_compare(item, (*node)->item);

		if (comp < 0) {
			// General case: check the left subsource.
			inserted = bst_insert_aux(source, &(*node)->left, item);
		} else if (comp > 0) {
			// General case: check the right subsource.
			inserted = bst_insert_aux(source, &(*node)->right, item);
		}
	}
	if (inserted) {
		// Update the node height if any of its children have been changed.
		bst_update_height(*node);
	}
	return inserted;
}

//--------------------------------------------------------------------
// Functions

// Initializes a BST.
bst_linked *bst_initialize() {
	bst_linked *source = malloc(sizeof *source);
	source->root = NULL;
	source->count = 0;
	return source;
}

/**
 * Helper function to recursively free a BST node and its children.
 *
 * @param node - pointer to the node to free
 */
static void bst_free_aux(bst_node **node) {
	if (*node == NULL) {
		return;
	}
	// Post-order traversal to free nodes
	bst_free_aux(&(*node)->left);
	bst_free_aux(&(*node)->right);

	// Free the node's data and then the node itself
	free((*node)->item);
	free(*node);
	*node = NULL;
}

// frees a BST.
void bst_free(bst_linked **source) {
	if (source == NULL || *source == NULL) {
		return;
	}

	bst_free_aux(&(*source)->root);
	free(*source);
	*source = NULL;

	return;
}

// Determines if a BST is empty.
bool bst_empty(const bst_linked *source) {
	return (source == NULL || source->root == NULL);
}

// Determines if a BST is full.
bool bst_full(const bst_linked *source) {
	return false;
}

// Returns number of items in a BST.
int bst_count(const bst_linked *source) {
	if (source == NULL) {
		return 0;
	}
	return source->count;
}

/**
 * Helper function to traverse BST in inorder and copy data to array.
 *
 * @param node - pointer to the current node
 * @param items - array to store items
 * @param index - current index in array
 * @return updated index after adding items
 */
static int bst_inorder_aux(const bst_node *node, data_ptr *items, int index) {
	if (node == NULL) {
		return index;
	}

	// LVR (Left-Visit-Right) traversal
	index = bst_inorder_aux(node->left, items, index);

	// Copy the current node's item to the array
	items[index] = node->item;
	index++;

	// Recursively traverse the right subtree
	index = bst_inorder_aux(node->right, items, index);

	return index;
}

// Copies the contents of a BST to an array in inorder.
void bst_inorder(const bst_linked *source, data_ptr *items) {
	if (source == NULL || source->root == NULL || items == NULL) {
		return;
	}

	bst_inorder_aux(source->root, items, 0);
	return;
}

/**
 * Helper function to traverse BST in preorder and copy data to array.
 *
 * @param node - pointer to the current node
 * @param items - array to store items
 * @param index - current index in array
 * @return updated index after adding items
 */
static int bst_preorder_aux(const bst_node *node, data_ptr *items, int index) {
	if (node == NULL) {
		return index;
	}

	// VLR (Visit-Left-Right) traversal
	items[index] = node->item;
	index++;

	index = bst_preorder_aux(node->left, items, index);
	index = bst_preorder_aux(node->right, items, index);

	return index;
}

// Copies the contents of a BST to an array in preorder.
void bst_preorder(const bst_linked *source, data_ptr *items) {
	if (source == NULL || source->root == NULL || items == NULL) {
		return;
	}

	bst_preorder_aux(source->root, items, 0);
	return;
}

/**
 * Helper function to traverse BST in postorder and copy data to array.
 *
 * @param node - pointer to the current node
 * @param items - array to store items
 * @param index - current index in array
 * @return updated index after adding items
 */
static int bst_postorder_aux(const bst_node *node, data_ptr *items, int index) {
	if (node == NULL) {
		return index;
	}

	// LRV (Left-Right-Visit) traversal
	index = bst_postorder_aux(node->left, items, index);
	index = bst_postorder_aux(node->right, items, index);

	items[index] = node->item;
	index++;

	return index;
}

// Copies the contents of a BST to an array in postorder.
void bst_postorder(const bst_linked *source, data_ptr *items) {
	if (source == NULL || source->root == NULL || items == NULL) {
		return;
	}

	bst_postorder_aux(source->root, items, 0);
	return;
}

// Inserts a copy of an item into a BST.
bool bst_insert(bst_linked *source, const data_ptr item) {
	return bst_insert_aux(source, &(source->root), item);
}

/**
 * Retrieves a copy of a value matching key in a BST.
 * Iterative implementation.
 *
 * @param source - pointer to the BST
 * @param key - key to search for
 * @param item - pointer to store the found item
 * @return true if key found, false otherwise
 */
bool bst_retrieve(bst_linked *source, const data_ptr key, data_ptr item) {
	if (source == NULL || source->root == NULL || key == NULL || item == NULL) {
		return false;
	}

	// Start at the root
	bst_node *current = source->root;

	// Traverse the tree
	while (current != NULL) {
		int comp = data_compare(key, current->item);

		if (comp < 0) {
			// Key is smaller than current node, go left
			current = current->left;
		} else if (comp > 0) {
			// Key is larger than current node, go right
			current = current->right;
		} else {
			// Key found, copy data to item
			data_copy(item, current->item);
			return true;
		}
	}

	// Key not found
	return false;
}

/**
 * Finds the minimum node in a subtree.
 *
 * @param node - pointer to the root of the subtree
 * @return pointer to the minimum node
 */
static bst_node *bst_find_min_node(bst_node *node) {
	bst_node *current = node;

	// Keep going left until we hit a leaf
	while (current && current->left != NULL) {
		current = current->left;
	}

	return current;
}

/**
 * Helper function to recursively remove a node matching key from a BST.
 *
 * @param source - pointer to the BST
 * @param node - pointer to the current node pointer
 * @param key - key of the node to remove
 * @param item - pointer to copy the removed item to
 * @param success - flag to indicate if removal was successful
 * @return new root of the subtree after removal
 */
static bst_node *bst_remove_aux(bst_linked *source, bst_node *node,
																const data_ptr key, data_ptr item,
																bool *success) {
	if (node == NULL) {
		*success = false;
		return NULL;
	}

	int comp = data_compare(key, node->item);

	if (comp < 0) {
		// Key is less than current node, search left subtree
		node->left = bst_remove_aux(source, node->left, key, item, success);
	} else if (comp > 0) {
		// Key is greater than current node, search right subtree
		node->right = bst_remove_aux(source, node->right, key, item, success);
	} else {
		// Found the node to remove
		*success = true;

		// Copy item before removing
		data_copy(item, node->item);

		// Case 1: Node with no children or only one child
		if (node->left == NULL) {
			bst_node *temp = node->right;
			free(node->item);
			free(node);
			source->count--;
			return temp;
		} else if (node->right == NULL) {
			bst_node *temp = node->left;
			free(node->item);
			free(node);
			source->count--;
			return temp;
		}

		// Case 2: Node with two children
		// Get the inorder successor (smallest in the right subtree)
		bst_node *temp = bst_find_min_node(node->right);

		// Copy the inorder successor's data to this node
		free(node->item);
		node->item = malloc(sizeof *(node->item));
		data_copy(node->item, temp->item);

		// Delete the inorder successor
		node->right =
				bst_remove_aux(source, node->right, temp->item, item, success);

		// Since we've already decremented count and copied the data,
		// we need to avoid double-counting the removal
		if (*success) {
			source->count++;
		}
	}

	// Update height of the current node
	if (node != NULL) {
		bst_update_height(node);
	}

	return node;
}

// Removes a value matching key in a BST.
bool bst_remove(bst_linked *source, const data_ptr key, data_ptr item) {
	if (source == NULL || source->root == NULL || key == NULL || item == NULL) {
		return false;
	}

	bool success = false;
	source->root = bst_remove_aux(source, source->root, key, item, &success);

	return success;
}

/**
 * Helper function to recursively copy nodes from a source tree to a target
 * tree.
 *
 * @param target - pointer to the target node pointer
 * @param source - pointer to the source node
 * @return true if copy was successful, false otherwise
 */
static bool bst_copy_aux(bst_node **target, const bst_node *source) {
	if (source == NULL) {
		*target = NULL;
		return true;
	}

	// Create new node and copy data
	*target = malloc(sizeof **target);
	if (*target == NULL) {
		return false;
	}

	(*target)->item = malloc(sizeof *((*target)->item));
	if ((*target)->item == NULL) {
		free(*target);
		*target = NULL;
		return false;
	}

	data_copy((*target)->item, source->item);
	(*target)->height = source->height;

	// Recursively copy left and right subtrees
	bool success = bst_copy_aux(&((*target)->left), source->left);
	if (!success) {
		free((*target)->item);
		free(*target);
		*target = NULL;
		return false;
	}

	success = bst_copy_aux(&((*target)->right), source->right);
	if (!success) {
		// Free the left subtree we just created
		bst_free_aux(&((*target)->left));
		free((*target)->item);
		free(*target);
		*target = NULL;
		return false;
	}

	return true;
}

// Copies source to target.
void bst_copy(bst_linked **target, const bst_linked *source) {
	if (target == NULL || source == NULL) {
		return;
	}

	// Free the target if it already exists
	if (*target != NULL) {
		bst_free(target);
	}

	// Initialize a new empty target BST
	*target = bst_initialize();
	if (*target == NULL) {
		return;
	}

	// If source is empty, return the empty target
	if (source->root == NULL) {
		return;
	}

	// Copy tree structure recursively
	bool success = bst_copy_aux(&((*target)->root), source->root);
	if (success) {
		(*target)->count = source->count;
	} else {
		bst_free(target);
	}
}

// Finds the maximum item in a BST.
bool bst_max(const bst_linked *source, data_ptr item) {
	if (source == NULL || source->root == NULL || item == NULL) {
		return false;
	}

	// In a BST, the maximum item is always the rightmost node
	bst_node *current = source->root;

	while (current->right != NULL) {
		current = current->right;
	}

	// Copy the maximum value to item
	data_copy(item, current->item);
	return true;
}

// Finds the minimum item in a BST.
bool bst_min(const bst_linked *source, data_ptr item) {
	if (source == NULL || source->root == NULL || item == NULL) {
		return false;
	}

	// In a BST, the minimum item is always the leftmost node
	bst_node *current = source->root;

	while (current->left != NULL) {
		current = current->left;
	}

	// Copy the minimum value to item
	data_copy(item, current->item);
	return true;
}

/**
 * Helper function to count leaf nodes recursively.
 *
 * @param node - pointer to the current node
 * @return number of leaf nodes in the subtree
 */
static int bst_leaf_count_aux(const bst_node *node) {
	if (node == NULL) {
		return 0;
	}

	// If node is a leaf (has no children)
	if (node->left == NULL && node->right == NULL) {
		return 1;
	}

	// Recursively count leaves in left and right subtrees
	return bst_leaf_count_aux(node->left) + bst_leaf_count_aux(node->right);
}

// Finds the number of leaf nodes in a tree.
int bst_leaf_count(const bst_linked *source) {
	if (source == NULL || source->root == NULL) {
		return 0;
	}

	return bst_leaf_count_aux(source->root);
}

/**
 * Helper function to count nodes with one child.
 *
 * @param node - pointer to the current node
 * @return number of nodes with exactly one child
 */
static int bst_one_child_count_aux(const bst_node *node) {
	if (node == NULL) {
		return 0;
	}

	// Count current node if it has exactly one child
	int count = 0;
	if ((node->left == NULL && node->right != NULL) ||
			(node->left != NULL && node->right == NULL)) {
		count = 1;
	}

	// Add counts from left and right subtrees
	return count + bst_one_child_count_aux(node->left) +
				 bst_one_child_count_aux(node->right);
}

// Finds the number of nodes with one child in a tree.
int bst_one_child_count(const bst_linked *source) {
	if (source == NULL || source->root == NULL) {
		return 0;
	}

	return bst_one_child_count_aux(source->root);
}

/**
 * Helper function to count nodes with two children.
 *
 * @param node - pointer to the current node
 * @return number of nodes with exactly two children
 */
static int bst_two_child_count_aux(const bst_node *node) {
	if (node == NULL) {
		return 0;
	}

	// Count current node if it has two children
	int count = 0;
	if (node->left != NULL && node->right != NULL) {
		count = 1;
	}

	// Add counts from left and right subtrees
	return count + bst_two_child_count_aux(node->left) +
				 bst_two_child_count_aux(node->right);
}

// Finds the number of nodes with two children in a tree.
int bst_two_child_count(const bst_linked *source) {
	if (source == NULL || source->root == NULL) {
		return 0;
	}

	return bst_two_child_count_aux(source->root);
}

/**
 * Helper function to count nodes with zero, one, and two children in one pass.
 *
 * @param node - pointer to the current node
 * @param zero - pointer to count of nodes with zero children
 * @param one - pointer to count of nodes with one child
 * @param two - pointer to count of nodes with two children
 */
static void bst_node_counts_aux(const bst_node *node, int *zero, int *one,
																int *two) {
	if (node == NULL) {
		return;
	}

	// Count current node based on number of children
	if (node->left == NULL && node->right == NULL) {
		(*zero)++; // Zero children (leaf)
	} else if (node->left != NULL && node->right != NULL) {
		(*two)++; // Two children
	} else {
		(*one)++; // One child
	}

	// Process children recursively
	bst_node_counts_aux(node->left, zero, one, two);
	bst_node_counts_aux(node->right, zero, one, two);

	return;
}

// Determines the number of nodes with zero, one, and two children.
// (May not call bst_leaf_count, bst_one_child_count, or bst_two_child_count.)
void bst_node_counts(const bst_linked *source, int *zero, int *one, int *two) {
	if (source == NULL || zero == NULL || one == NULL || two == NULL) {
		return;
	}

	// Initialize counters
	*zero = 0;
	*one = 0;
	*two = 0;

	if (source->root == NULL) {
		return;
	}

	// Count nodes recursively
	bst_node_counts_aux(source->root, zero, one, two);

	return;
}

/**
 * Helper function to check if a tree is balanced.
 * A balanced tree is one where the heights of the two subtrees of any node
 * differ by no more than 1.
 *
 * @param node - pointer to the current node
 * @return true if the tree is balanced, false otherwise
 */
static bool bst_balanced_aux(const bst_node *node) {
	if (node == NULL) {
		return true;
	}

	// Get heights of left and right subtrees
	int left_height = bst_node_height(node->left);
	int right_height = bst_node_height(node->right);

	// Check if current node is balanced and recursively check children
	if (abs(left_height - right_height) <= 1 && bst_balanced_aux(node->left) &&
			bst_balanced_aux(node->right)) {
		return true;
	}

	return false;
}

// Determines whether or not a tree is a balanced tree.
bool bst_balanced(const bst_linked *source) {
	if (source == NULL) {
		return true; // Empty tree is balanced
	}

	return bst_balanced_aux(source->root);
}

/**
 * Helper function to check if a tree follows BST property.
 * All nodes on the left must be less than the node and all nodes
 * on the right must be greater than the node.
 *
 * @param node - pointer to the current node
 * @param min - pointer to minimum allowed value (NULL if no minimum)
 * @param max - pointer to maximum allowed value (NULL if no maximum)
 * @return true if the tree is a valid BST, false otherwise
 */
static bool bst_valid_aux(const bst_node *node, const data_ptr min,
													const data_ptr max) {
	if (node == NULL) {
		return true;
	}

	// Check if current node's value is within allowed range
	if ((min != NULL && data_compare(node->item, min) <= 0) ||
			(max != NULL && data_compare(node->item, max) >= 0)) {
		return false;
	}

	// Recursively validate left and right subtrees
	// For left subtree: current node's value becomes the max
	// For right subtree: current node's value becomes the min
	return bst_valid_aux(node->left, min, node->item) &&
				 bst_valid_aux(node->right, node->item, max);
}

// Determines whether or not a tree is a valid BST.
bool bst_valid(const bst_linked *source) {
	if (source == NULL) {
		return true; // Empty tree is a valid BST
	}

	return bst_valid_aux(source->root, NULL, NULL);
}

/**
 * Helper function to check if two trees are equal (same structure and data).
 *
 * @param node1 - pointer to the first tree node
 * @param node2 - pointer to the second tree node
 * @return true if trees are equal, false otherwise
 */
static bool bst_equals_aux(const bst_node *node1, const bst_node *node2) {
	// If both are NULL, they're equal
	if (node1 == NULL && node2 == NULL) {
		return true;
	}

	// If only one is NULL, they're not equal
	if (node1 == NULL || node2 == NULL) {
		return false;
	}

	// Compare data and heights
	if (data_compare(node1->item, node2->item) != 0 ||
			node1->height != node2->height) {
		return false;
	}

	// Recursively check left and right subtrees
	return bst_equals_aux(node1->left, node2->left) &&
				 bst_equals_aux(node1->right, node2->right);
}

// Determines if two trees contain same data in same configuration.
bool bst_equals(const bst_linked *target, const bst_linked *source) {
	// Handle NULL cases
	if (target == NULL && source == NULL) {
		return true;
	}

	if (target == NULL || source == NULL) {
		return false;
	}

	// Check if counts are equal
	if (target->count != source->count) {
		return false;
	}

	// If both empty, they're equal
	if (target->root == NULL && source->root == NULL) {
		return true;
	}

	// Check if tree structures and data are equal
	return bst_equals_aux(target->root, source->root);
}

/**
 * Private helper function to print contents of BS in preorder.
 *
 * @param to_string - function to print data_ptr
 * @param node - pointer to bst_node
 */
static void bst_print_aux(bst_node *node) {
	char string[DATA_STRING_SIZE];

	if (node != NULL) {
		data_string(string, DATA_STRING_SIZE, node->item);
		printf("%s\n", string);
		bst_print_aux(node->left);
		bst_print_aux(node->right);
	}
	return;
}

// Prints the items in a BST in preorder.
void bst_print(const bst_linked *source) {
	printf("  count: %d, height: %d, items:\n", source->count,
				 source->root->height);
	bst_print_aux(source->root);
	printf("\n");
	return;
}
