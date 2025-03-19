/*
--------------------------------------------------
Project: a8q2
File:    set_avl_ptest.c
Description: public test driver program
Author:  HBF  
Version: 2025-02-23
--------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "avl.h"
#include "set_avl.h"

char *tests[] = { "a", "a",  "b",  "c",  "d", "aa", "bb",  "cc", "dd" };
char *contain_tests[] = { "a", "aa", "A"};
char *remove_tests[] = { "a", "aa", "A"};
SET set={0};

void display_inorder_line(AVLNODE *root);
void display_set_info(SET *set, char *prefix);


void test_before() {
	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
		set_add(&set, tests[i]);
	}
    display_set_info(&set, "after set_add");
	printf("\n");
}

void test_after() {
	avl_clean(&set.root);
}

void test_set_size() {
	printf("------------------\n");
	printf("Test: set_size\n\n");
	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n/2; i=i+2) {
		set_add(&set, tests[i]);
		printf("%s(%s): %d ", "set_add_set_size", tests[i], set.size);
		display_inorder_line(set.root);
		printf("\n");
	}
	for (int i = 0; i < n/2; i=i+2) {
		set_remove(&set, tests[i]);
		printf("%s(%s): %d ", "set_remove_set_size", tests[i], set.size);
		display_inorder_line(set.root);
		printf("\n");
	}
	printf("\n");
}


void test_set_add() {
	printf("------------------\n");
	printf("Test: set_add\n\n");
	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
		set_add(&set, tests[i]);
		printf("%s(%s):", "set_add", tests[i]);
		display_inorder_line(set.root);
		printf("\n");
	}
}

void test_set_contain() {
	printf("------------------\n");
	printf("Test: set_contain \n\n");
	int n = sizeof contain_tests / sizeof *contain_tests;
	for (int i = 0; i < n; i++) {
		int p = set_contain(&set, contain_tests[i]);
		printf("%s(%s): %d", "set_contain", remove_tests[i], p);
		printf("\n");
	}
	printf("\n");
}

void test_set_remove() {
	printf("------------------\n");
	printf("Test: set_remove\n\n");
	int n = sizeof remove_tests / sizeof *remove_tests;
	for (int i = 0; i < n; i++) {
		printf("%s(%s): ", "set_remove", remove_tests[i]);
		set_remove(&set, remove_tests[i]);
		display_inorder_line(set.root);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char* args[]) {
	test_set_size();
	test_set_add();
	test_set_contain();
	test_set_remove();
	test_after();
	return 0;
}

void display_set_info(SET *s, char *prefix) {
  printf("%s set_size(set):%d\n", prefix, set_size(s));
  if (set_size(s) == 0)
    printf("%s elements:%s", prefix, "empty");
  else {
    printf("%s elements:", prefix); 
    display_inorder_line(s->root);
  }
  printf("\n"); 
}

void display_inorder_line(AVLNODE *root) {
	if (root) {
		if (root->left)
			display_inorder_line(root->left);
		printf("%s ", root->data.name, root->data.score);
		if (root->right)
			display_inorder_line(root->right);
	}
}

