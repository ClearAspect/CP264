#include "set_avl.h"
#include <stdlib.h>
#include <string.h>

int set_size(SET *s) {
	return s->size;
}

int set_contain(SET *s, char *e) {

	AVLNODE *np = avl_search(s->root, e);
	if (np == NULL) {
		return 0;
	}
	return 1;
}

void set_add(SET *s, char *e) {
	if (set_contain(s, e)) {
		return; // Element already exists, no need to add again
	}

	RECORD record;
	strcpy(record.name, e); // Copy the string to the record's name field
	record.score = 0.0;			// Default score value, not used for set operations

	avl_insert(&(s->root), record);
	s->size++;
}

void set_remove(SET *s, char *e) {
	if (!set_contain(s, e)) {
		return;
	}

	avl_delete(&(s->root), e);
	s->size--;
}

void set_clean(SET *s) {
	avl_clean(&(s->root));
	s->size = 0;
}
