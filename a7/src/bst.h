
#ifndef BST_H
#define BST_H

typedef struct record {
	char name[20];
	float score;
} RECORD;

typedef struct bstnode BSTNODE;

struct bstnode {
	RECORD data;
	BSTNODE *left;
	BSTNODE *right;
};

/* This function creates BSTNODE node with given RECORD data
 * using malloc() and return the new node pointer.
 */
BSTNODE *bst_node(RECORD data);

/* Search the BST by search key matching with data.name
 *
 * @param root - pointer to tree root.
 * @param key - string of search key
 *
 * @return - pointer to matched node if found, otherwise NULL
 */
BSTNODE *bst_search(BSTNODE *root, char *key);

/* Insert a node of given record data into BST.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  -  record data for the new node.
 *
 */
void bst_insert(BSTNODE **rootp, RECORD data);

/* Delete a node of data.name matched with given key.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void bst_delete(BSTNODE **rootp, char *key);

/* This function cleans the BST passed by pointer of root pointer.
 * @param rootp - pointer to pointer of a tree node.
 */
void bst_clean(BSTNODE **rootp);

/* Get and return and remove the smallest data.name node from the BST.
 *
 * @param rootp - pointer of pointer to BST root.
 * @return - node pointer of the extracted smallest node with NULL childern.
 */
BSTNODE *extract_smallest_node(BSTNODE **rootp);

#endif
