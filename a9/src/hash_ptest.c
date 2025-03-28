/*
 -------------------------------------------------------
 File:     hash_ptest.c
 About:    public test driver
 Author:   HBF
 Version:  2025-03-13
 -------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

int htsize = 5;
void search_info(char *key, HNODE *p);
void display_hashtable(HASHTABLE *ht, int option);

DATA tests[] = { { "a", 0 }, { "b", 1 }, { "c", 2 }, { "d", 3 }, { "e", 4 },
		{ "f", 5 }, { "g", 6 } };
char search_tests[][20] = { "a", "b", "f", "h" };
char delete_tests[][20] = { "a", "b", "f", "h" };
HASHTABLE *ht = NULL;

void test_hash() {
	printf("------------------\n");
	printf("Test: hash\n\n");
	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
		printf("%s(%s): %d\n", "hash", tests[i].name,
				hash(tests[i].name, htsize));
	}
	printf("\n");
}

void test_new_hahstable() {
	printf("------------------\n");
	printf("Test: new_hashtable\n\n");
	HASHTABLE *ht = new_hashtable(htsize);
	printf("%s(%d): size %d count %d", "new_hashtable", htsize, ht->size,
			ht->count);
	printf("\n");
}

void test_hahstable_insert() {
	printf("------------------\n");
	printf("Test: hashtable_insert\n\n");
	int n = sizeof tests / sizeof *tests;
	ht = new_hashtable(htsize);
	for (int i = 0; i < n; i++) {
		hashtable_insert(ht, tests[i]);
		printf("%s(%s %d): ", "hashtable_insert", tests[i].name, tests[i].value);
		display_hashtable(ht, 1);
		printf("\n");
	}
	printf("\n");
}

void test_hahstable_delete() {
	printf("------------------\n");
	printf("Test: hashtable_delete\n\n");
	int n = sizeof delete_tests / sizeof *delete_tests;
	for (int i = 0; i < n; i++) {
		hashtable_delete(ht, delete_tests[i]);
		printf("%s(%s): ", "hashtable_delete", delete_tests[i]);
		display_hashtable(ht, 1);
		printf("\n");
	}
	printf("\n");
}

void test_hahstable_search() {
	printf("------------------\n");
	printf("Test: hashtable_search\n\n");
	int n = sizeof search_tests / sizeof *search_tests;
	for (int i = 0; i < n; i++) {
		HNODE *hnp = hashtable_search(ht, search_tests[i]);
		search_info(search_tests[i], hnp);
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	test_hash();
	test_new_hahstable();
	test_hahstable_insert();
	test_hahstable_search();
	test_hahstable_delete();
	hashtable_clean(&ht);
	return 0;
}

void search_info(char *key, HNODE *p) {
	if (p)
		printf("search(%s):(%s,%d)\n", key, p->data.name, p->data.value);
	else
		printf("search(%s):NULL\n", key);
}

void display_hashtable(HASHTABLE *ht, int option) {
	int i = 0;
	HNODE *p;
	if (option == 0) {
		printf("size:%d\n", ht->size);
		printf("count:%d", ht->count);
		for (i = 0; i < ht->size; i++) {
			p = *(ht->hna + i);
			if (!p)
				printf("\n%d:NULL", i);
			else {
				printf("\n%d:", i);
				while (p) {
					printf("(%s,%d) ", p->data.name, p->data.value);
					p = p->next;
				}
			}
		}
		printf("\n");
	} else {
		printf("count %d ", ht->count);
		for (i = 0; i < ht->size; i++) {
			p = *(ht->hna + i);
			if (p) {
				printf("%d ", i);
				while (p) {
					printf("(%s %d) ", p->data.name, p->data.value);
					p = p->next;
				}
			}
		}
	}
}

