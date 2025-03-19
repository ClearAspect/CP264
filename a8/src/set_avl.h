
#ifndef SET_AVL
#define SET_AVL

#include "avl.h"

typedef struct {
	int size;
	AVLNODE *root;
} SET;

/**
 * returns the number of elements in the set
 */
int set_size(SET *s);

/**
 * Returns 1 it set s contains element e; otherwise 0.
 */
int set_contain(SET *s, char *e);

/**
 * Add element e into set s.
 */
void set_add(SET *s, char *e);

/**
 * Remove  element e into set s
 */
void set_remove(SET *s, char *e);

/**
 * Clear the set, clearing the underlying AVL tree, and reset fields of s.
 */
void set_clean(SET *s);

#endif // !SET_AVL
