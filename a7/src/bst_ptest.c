/*
-------------------------------------------------------
File:     bst_ptest.c
About:    public test driver
Author:   HBF
Version:  2025-02-30
-------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

void display_tree(BSTNODE *root, int pretype, int prelen);
void display_inorder_line(BSTNODE *root);
void search_info(char *sf, char *key, BSTNODE *tnp);

RECORD tests[] = { { "A4", 40 },  { "A1", 10 }, { "A2", 20 }, { "A3", 30 },  { "A8", 80 }, {
		"A5", 50 }, { "A6", 60 }, { "A7", 70 }, { "A9", 90 }, {
		"B1", 100 } };

char *search_keys[] = { "A2", "A4", "B2", "A8" };
char *delete_keys[] = { "A1", "A3", "A5", "B1" };

BSTNODE *root = NULL;

void test_start() {
	printf("------------------\n");
	printf("Test: start\n\n");

	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
	   bst_insert(&root, tests[i]);
	}
	display_tree(root, 0, 0);
	printf("\n");
}


void test_bst_insert() {
	printf("------------------\n");
	printf("Test: bst_insert \n\n");

	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
		bst_insert(&root, tests[i]);
		if (i % 2 == 0) {
			printf("%s(%s %0.1f):", "bst_insert", tests[i].name,  tests[i].score);
			display_inorder_line(root);
			printf("\n");
		}
	}
	//display_tree(root, 0, 0);
	printf("\n");
}

void test_bst_search() {
	printf("------------------\n");
	printf("Test: bst_search \n\n");

	int n = sizeof search_keys / sizeof *search_keys;
	BSTNODE *p = NULL;
	for (int i = 0; i < n; i++) {
		p = bst_search(root, search_keys[i]);
		search_info("bst_search", search_keys[i], p);
		printf("\n");
	}
	printf("\n");
}

void test_end() {
	printf("------------------\n");
	printf("Test: end\n\n");
	bst_clean(&root);
}

void test_bst_delete() {
	printf("------------------\n");
	printf("Test: bst_delete\n\n");
	int n = sizeof delete_keys / sizeof *delete_keys;
	for (int i = 0; i < n; i++) {
		printf("%s(%s): ", "bst_delete", delete_keys[i]);
		bst_delete(&root, delete_keys[i]);
		display_inorder_line(root);
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char* args[]) {
	test_bst_insert();
	test_bst_search();
	test_bst_delete();
	bst_clean(&root);
  return 0;
}


void search_info(char *sf, char *key, BSTNODE *tnp){
  if (tnp)
    printf("%s(%s): %s %.1f", sf, key, tnp->data.name, tnp->data.score);
  else
    printf("%s(%s): NULL", sf, key);
}

void display_inorder_line(BSTNODE *root) {
  if (root) {
    if (root->left) display_inorder_line(root->left);
    printf("%s ", root->data.name);
    //printf("%s %.1f ", root->data.name, root->data.score);
    if (root->right) display_inorder_line(root->right);
  }
}


void display_tree(BSTNODE *root, int pretype, int prelen) {
  if (root) {
    int i;
    for (i = 0; i < prelen; i++) {
      printf("%c", ' ');
	}
	if (pretype == 0)
      printf("%s", "|___:");
	else if (pretype == 1)
      printf("%s", "|___L:");
	else if (pretype == 2)
      printf("%s", "|___R:");
    printf("%s,%.1f\n", root->data.name,root->data.score);
    display_tree(root->right, 2, prelen + 4);
    display_tree(root->left, 1, prelen + 4);
  }
}

