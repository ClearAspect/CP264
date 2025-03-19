/*
 -------------------------------------------------------
 File:     avl_ptest.c
 About:    public test driver
 Author:   HBF
 Version:  2025-03-02
 -------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

#define SHOWTREE1
//#define SHOWTREES

void display_tree(AVLNODE *root, int pretype, int prelen);
void display_inorder_line(AVLNODE *root);
void search_info(char *sf, char *key, AVLNODE *tnp);

/* Checks if a tree is AVL tree.
 *
 * @param root - the root of the  tree
 * @return - 1 if true, 0 otherwise
 */
int is_avl(AVLNODE *root) {
	if (root) {
		int lh = (root->left) ? root->left->height : 0;
		int rh = (root->right) ? root->right->height : 0;
		int bf = lh - rh;
		if (bf > 1 || bf < -1)
			return 0;
		if (root->left && is_avl(root->left) == 0)
			return 0;
		if (root->right && is_avl(root->right) == 0)
			return 0;
	}
	return 1;
}

RECORD tests[] = { { "A01", 10 }, { "A02", 20 }, { "A03", 30 }, { "A04", 40 }, {
		"A05", 50 }, { "A06", 60 }, { "A07", 70 } };
char *search_keys[] = { "A02", "A04", "A08" };
char *delete_keys[] = { "A01", "A03", "A04" };
AVLNODE *root = NULL;

void test_before() {
	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
		avl_insert(&root, tests[i]);
	}
#ifdef SHOWTREES
	display_tree(root, 0, 0);
#endif
	printf("%s(%s): %d", "is_avl", root->data.name, is_avl(root));
	printf("\n");
}

void test_after() {
	avl_clean(&root);
}

void test_avl_insert() {
	printf("------------------\n");
	printf("Test: avl_insert\n\n");

	int n = sizeof tests / sizeof *tests;
	for (int i = 0; i < n; i++) {
		avl_insert(&root, tests[i]);
		printf("%s(%s %0.1f):", "avl_insert", tests[i].name, tests[i].score);

#ifdef SHOWTREES
		printf("\n");
		display_tree(root, 0, 0);
		printf("\n");

#else
		display_inorder_line(root);
		printf("\n");
#endif

	}

	#ifdef SHOWTREE1
		printf("\n");
		display_tree(root, 0, 0);
		printf("\n");
	#endif	

	printf("%s(%s): %d\n", "height", root->data.name, height(root));
	printf("%s(%s): %d\n", "balance_factor", root->data.name,
			balance_factor(root));
	printf("%s(%s): %d", "is_avl", root->data.name, is_avl(root));
	printf("\n");
}

void test_avl_search() {
	printf("------------------\n");
	printf("Test: avl_search \n\n");
	int n = sizeof search_keys / sizeof *search_keys;
	AVLNODE *p = NULL;
	for (int i = 0; i < n; i++) {
		p = avl_search(root, search_keys[i]);
		search_info("avl_search", search_keys[i], p);
		printf("\n");
	}
	printf("\n");
}

void test_avl_delete() {
	printf("------------------\n");
	printf("Test: avl_delete\n\n");
	int n = sizeof delete_keys / sizeof *delete_keys;
	for (int i = 0; i < n; i++) {
		printf("%s(%s): ", "avl_delete", delete_keys[i]);

		avl_delete(&root, delete_keys[i]);
#ifdef SHOWTREES
		printf("\n");
		display_tree(root, 0, 0);
		printf("\n");
#else
		display_inorder_line(root);
		printf("\n");
#endif
	}
	printf("%s(%s): %d\n", "height", root->data.name, height(root));
	printf("%s(%s): %d\n", "balance_factor", root->data.name,
			balance_factor(root));
	printf("%s(%s): %d", "is_avl", root->data.name, is_avl(root));

	printf("\n");
}

int main(int argc, char* args[]) {
	test_avl_insert();
	test_avl_search();
	test_avl_delete();
	test_after();
	return 0;
}

void search_info(char *sf, char *key, AVLNODE *tnp) {
	if (tnp)
		printf("%s(%s): %s %.1f", sf, key, tnp->data.name, tnp->data.score);
	else
		printf("%s(%s): NULL", sf, key);
}

void display_inorder_line(AVLNODE *root) {
	if (root) {
		if (root->left)
			display_inorder_line(root->left);
		printf("%s %.1f ", root->data.name, root->data.score);
		if (root->right)
			display_inorder_line(root->right);
	}
}

void display_tree(AVLNODE *root, int pretype, int prelen) {
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
		printf("%s,%.1f,%d\n", root->data.name, root->data.score, root->height);
		display_tree(root->right, 2, prelen + 4);
		display_tree(root->left, 1, prelen + 4);
	}
}
