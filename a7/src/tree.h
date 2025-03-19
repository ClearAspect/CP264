
#ifndef TREE_H
#define TREE_H

/* Define node structure of a binary tree
 * data - data field of tree node
 * left - pointer to the left child
 * right - pointer to the right child
 */
typedef struct tnode {
	char data;
	struct tnode *left;
	struct tnode *right;
} TNODE;

/* Define a structure to represent tree properties.
 * order - the number of nodes
 * height - the height
 */
typedef struct tree_props {
	int order;
	int height;
} TPROPS;

/* Compute and return the TPROPS value of a tree.
 * @param root - pointer to the root of a tree
 * @return - number of nodes and height in TPROPS type.
 */
TPROPS tree_property(TNODE *root);

/* Display the node data of the tree in pre-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void preorder(TNODE *root);

/* Display the node data of the tree in in-order and format "%c".
 *
 *  @param root - pointer to the root of a tree
 */
void inorder(TNODE *root);

/* Display the node data of the tree in post-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void postorder(TNODE *root);

/* Display the node data of the tree in breadth-first-order and format "%c ".
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 */
void bforder(TNODE *root);

/* Search by key using breadth-first-search algorithm
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *bfs(TNODE *root, char key);

/* Search by key using depth-first-search algorithm.
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *dfs(TNODE *root, char key);

// The following functions are given in a7 help.

/* Create a TNODE node and sets the data to value and returns the pointer.
 * Use malloc()
 */
TNODE *tree_node(char val);

/* This function cleans a tree.
 * @param rootp - pointer of pointer to the tree root
 */
void clean_tree(TNODE **rootp);

/* This function creates a new node of given value and inserts it into a tree
 * at the first available position in order of breadth-first and left to right.
 *
 * @param rootp - pointer of pointer to the tree node.
 * @param val - data for the new node.
 */
void insert_tree(TNODE **rootp, char val);

#endif
