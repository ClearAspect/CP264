
#ifndef MYRECORD_AVL_H
#define MYRECORD_AVL_H

#include "avl.h"

/*  This structure holds the root pointer of AVL tree data structure,
 *  and count, mean and stddev of the data.score in the AVL tree.
 */
typedef struct {
	AVLNODE *root;
	int count;
	float mean;
	float stddev;
} AVLDS;

/*  Merge source AVL tree into destination AVL tree. No change to source tree.
 *  @parame rootp_dest   - pointer to pointer of root of destination tree
 *  @parame rootp_source - pointer to pointer of root of source tree
 */
void avl_merge(AVLNODE **rootp_dest, AVLNODE **rootp_source);

/*  Merge source AVLDS to destination AVLDS, use aggregation algorithm to
 *  compute the stats info, can clean source AVLDS.
 *  @parame source - pointer to the source AVLDS
 *  @parame dest - pointer to the destination AVLDS
 */
void avlds_merge(AVLDS *dest, AVLDS *source);

/*  Clean its AVL tree and set count=0, mean=0, stddev=0
 *  @parame ds - pointer to the AVLDS
 */
void avlds_clean(AVLDS *ds);

// The following two functions are similar to that of A7Q3.
void add_record(AVLDS *ds, RECORD data);
void remove_record(AVLDS *ds, char *name);

#endif // !MYRECORD_AVL_H
