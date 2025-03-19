/*
 -------------------------------------------------------
 File:     tree_ptest.c
 About:    public test driver
 Author:   HBF
 Version:  2025-02-28
 -------------------------------------------------------
 */

#include <stdio.h>
#include "tree.h"

void search_info(char *sf, char key, TNODE *tnp);
void display_tree(TNODE *root, int pretype, int prelen);


char tree_tests[] = { '*', '+', '-', '1', '2', '4', '1' };
char bfs_tests[] = { '+', '-', '1', 'B' };
char dfs_tests[] = { '3', '-', '*', 'F' };


TNODE *root = NULL;

void test_before() {
	printf("------------------\n");
	printf("Test start: create testing tree\n\n");
	int n = sizeof tree_tests / sizeof *tree_tests;
	for (int i = 0; i < n; i++) {
		insert_tree(&root, tree_tests[i]);
	}
	display_tree(root, 0, 0);
	printf("\n");
}

void test_end() {
	printf("------------------\n");
	printf("Test end: clean testing tree\n\n");
	clean_tree(&root);
	printf("\n");
}

void test_tree_property() {
	printf("------------------\n");
	printf("Test: tree_property\n\n");
	TPROPS property = tree_property(root);
	printf("tree_property(%s).order: %d\n", "root", property.order);
	printf("tree_property(%s).height: %d\n", "root", property.height);
	printf("\n");
}

void test_preorder() {
	printf("------------------\n");
	printf("Test: preorder\n\n");
	printf("preorder(%s): ", "root");
	preorder(root);
	printf("\n");
}

void test_inorder() {
	printf("------------------\n");
	printf("Test: inorder\n\n");
	printf("inorder(%s): ", "root");
	inorder(root);
	printf("\n");
}

void test_postorder() {
	printf("------------------\n");
	printf("Test: postorder\n\n");
	printf("postorder(%s): ", "root");
	postorder(root);
	printf("\n");
}

void test_bforder() {
	printf("------------------\n");
	printf("Test: bforder\n\n");
	printf("bforder(%c): ", root->data);
	bforder(root);
	printf("\n");

	printf("bforder(%c): ", root->left->data);
	bforder(root->left);
	printf("\n");

	printf("bforder(%c): ", root->right->data);
	bforder(root->right);
	printf("\n");
}

void test_bfs() {
	printf("------------------\n");
	printf("Test: bfs\n\n");
	TNODE *tp = NULL;
	int n = sizeof bfs_tests / sizeof *bfs_tests;
	for (int i = 0; i < n; i++) {
		tp = bfs(root, bfs_tests[i]);
		search_info("bfs", bfs_tests[i], tp);
	}
	printf("\n");
}

void test_dfs() {
	printf("------------------\n");
	printf("Test: dfs\n\n");
	TNODE *tp = NULL;
	int n = sizeof dfs_tests / sizeof *dfs_tests;
	for (int i = 0; i < n; i++) {
		tp = dfs(root, dfs_tests[i]);
		search_info("dfs", dfs_tests[i], tp);
	}
	printf("\n");
}

void search_info(char *sf, char key, TNODE *tnp);
void display_tree(TNODE *root, int pretype, int prelen);

int main() {
	test_before();
	test_tree_property();
	test_preorder();
	test_inorder();
	test_postorder();
	test_bforder();
	test_bfs();
	test_dfs();
	test_end();

	return 0;
}

void search_info(char *sf, char key, TNODE *tnp) {
	if (tnp)
		printf("\n%s(%c): %c", sf, key, tnp->data);
	else
		printf("\n%s(%c): NULL", sf, key);
}

void display_tree(TNODE *root, int pretype, int prelen) {
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

		printf("%c\n", root->data);
		display_tree(root->right, 2, prelen + 4);
		display_tree(root->left, 1, prelen + 4);
	}
}

