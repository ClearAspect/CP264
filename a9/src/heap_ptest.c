/*--------------------------------------------------
 File:    heap_ptest.c
 About:   public test driver
 Author:  HBF
 Version: 2025-03-13
 --------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "heap.h"

void display_heap(HEAP *hp);
void display_data(HEAPDATA *tests, int n);

int c = 4;  // initial capacity
HEAPDATA tests[] = { { 4, 10 }, { 5, 9 }, { 8, 6 }, { 7, 7 }, { 6, 8 }, { 12, 2 }, { 9, 5 } };
//HEAPDATA tests[] = { { 4, 10 }, { 5, 9 }, { 8, 6 }, { 7, 7 }, { 6, 8 }, { 12, 2 }, { 9, 5 }, { 13, 1 }, { 10, 4 }, { 11, 3 } };
//HEAPDATA tests[] = { { 1, 10 }, { 2, 20 }, { 3, 30 }, { 4, 40 }, { 5, 50 }, {6, 60 } };	
VALUETYPE search_data_tess[] = { 10, 6, 1 };

typedef struct {
	int index;
	KEYTYPE key;
} INDEXKEY;

INDEXKEY change_key_tests[] = { { 0, 8 }, { 3, 1 } };

HEAP *hp = NULL;

void test_new_heap() {
	printf("------------------\n");
	printf("Test: new_heap\n\n");
	hp = new_heap(c);
	printf("%s(%d): ", "new_heap", c);
	display_heap(hp);
	printf("\n");
}

void test_heap_insert() {
	printf("------------------\n");
	printf("Test: heap_insert\n\n");
	printf("%s: ", "heap_insert");
	display_heap(hp);
	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
		heap_insert(hp, tests[i]);
		printf("%s(%d %d): size %d capacity %d\n", "heap_insert", tests[i].key,
				tests[i].value, hp->size, hp->capacity);
	}
	printf("%s: ", "after heap_insert");
	display_heap(hp);
	printf("\n");
}

void test_before() {
	hp = new_heap(c);
	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
		heap_insert(hp, tests[i]);
	}
}

void test_after() {
	heap_clean(&hp);
}

void test_heap_search_value() {
	printf("------------------\n");
	printf("Test: heap_search_value\n\n");
	printf("%s: ", "heap_search_value");
	display_heap(hp);
	int n = sizeof search_data_tess / sizeof *search_data_tess;
	for (int i = 0; i < n; i++) {
		int index = heap_search_value(hp, search_data_tess[i]);
		if (index >= 0)
			printf("%s(%d): index %d key %d data %d\n", "heap_search_value",
					search_data_tess[i], index, hp->hda[index].key,
					hp->hda[index].value);
		else
			printf("%s(%d): not found\n", "heap_search_value",
					search_data_tess[i]);
	}
	printf("\n");
}

void test_heap_extract_min() {
	printf("------------------\n");
	printf("Test: heap_extract_min and heap_find_min\n\n");
	printf("%s: ", "heap_extract_min");
	display_heap(hp);
	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n / 2; i++) {
		HEAPDATA hd = heap_extract_min(hp);
		printf("%s(%d): key %d data %d  size %d capacity %d\n",
				"heap_extract_min", i, hd.key, hd.value, hp->size, hp->capacity);
		hd = heap_find_min(hp);
		printf("%s(%d): key %d data %d\n", "heap_find_min", i, hd.key, hd.value);
	}
	printf("\n");
}

void test_heap_change_key() {
	printf("------------------\n");
	printf("Test: heap_change_key\n\n");
	printf("%s: ", "heap_change_key");
	display_heap(hp);
	int n = sizeof change_key_tests / sizeof *change_key_tests;
	for (int i = 0; i < n; i++) {
		HEAPDATA hd = hp->hda[change_key_tests[i].index];
		int index = heap_change_key(hp, change_key_tests[i].index,
				change_key_tests[i].key);
		printf("%s(%d %d): (%d %d %d) -> (%d %d %d)\n", "heap_change_key",
				change_key_tests[i].index, change_key_tests[i].key,
				change_key_tests[i].index, hd.key, hd.value, index,
				hp->hda[index].key, hp->hda[index].value);
	}
	printf("%s: ", "after heap_change_key");
	display_heap(hp);
	printf("\n");
}

void test_heap_sort() {
	printf("------------------\n");
	printf("Test: heap_sort\n\n");
	int n = sizeof tests / sizeof *tests;
	printf("before_heap_sort: ");
	display_data(tests, n);
	heap_sort(tests, n);
	printf("after_heap_sort: ");
	display_data(tests, n);
	printf("\n");
}

int main(int argc, char *args[]) {
	test_new_heap();
	test_heap_insert();
	test_heap_search_value();
	test_heap_change_key();
	test_after();
	test_before();
	test_heap_extract_min();
	test_after();
	test_heap_sort();
	return 0;
}

void display_heap(HEAP *hp) {
	printf("size %d capacity %d ", hp->size, hp->capacity);
	printf("(index key data) ");
	for (int i = 0; i < hp->size; i++) {
		printf("(%d %d %d) ", i, hp->hda[i].key, hp->hda[i].value);
	}
	printf("\n");
}

void display_data(HEAPDATA *tests, int n) {
	for (int i = 0; i < n; i++) {
		printf("(%d %d) ", tests[i].key, tests[i].value);
	}
	printf("\n");
}
