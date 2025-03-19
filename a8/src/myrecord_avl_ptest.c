/*
 -------------------------------------------------------
 File:     myrecord_avl_ptest.c
 About:    public test driver
 Author:   HBF
 Version:  2025-03-22
 -------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "avl.h"
#include "myrecord_avl.h"

#define EPSILON 0.00001

void display_stats(const AVLDS *root);
int is_avl(AVLNODE *root);
void display_inorder(AVLNODE *root);

RECORD testsA[] = { { "A01", 10 }, { "A02", 20 }, { "A03", 30 }, { "A04", 40 },
		{ "A05", 50 }, { "A06", 60 }, { "A07", 70 }, { "A08", 80 },
		{ "A09", 90 }, { "A10", 100 } };

RECORD testsB[] = { { "B01", 10 }, { "B02", 20 }, { "B03", 30 }, { "B04", 40 },
		{ "B05", 50 }, { "B06", 60 }, { "B07", 70 }, { "B08", 80 },
		{ "B09", 90 }, { "B10", 100 } };

RECORD testsC[] = { { "A01", 10 }, { "A02", 20 }, { "A03", 30 }, { "A04", 40 },
		{ "A05", 50 }, { "A06", 60 }, { "A07", 70 }, { "A08", 80 },
		{ "A09", 90 }, { "A10", 100 }, { "B01", 10 }, { "B02", 20 },
		{ "B03", 30 }, { "B04", 40 }, { "B05", 50 }, { "B06", 60 },
		{ "B07", 70 }, { "B08", 80 }, { "B09", 90 }, { "B10", 100 }, };

AVLNODE *avlA = NULL;
AVLNODE *avlB = NULL;
AVLDS avldsA = { 0 };
AVLDS avldsB = { 0 };
AVLDS avldsC = { 0 };

void test_avl_merge() {
	printf("------------------\n");
	printf("Test: avl_merge\n\n");
	int n = sizeof testsA / sizeof *testsA;
	for (int i = 0; i < n; i++) {
		avl_insert(&avlA, testsA[i]);
	}
	printf("%s(%s): %d\n", "is_avl", "avlA", is_avl(avlA));

	n = sizeof testsB / sizeof *testsB;
	for (int i = 0; i < n; i++) {
		avl_insert(&avlB, testsB[i]);
	}
	printf("%s(%s): %d\n", "is_avl", "avlB", is_avl(avlB));

	avl_merge(&avlA, &avlB);
	printf("%s(%s): %d", "avl_merge", "avlA avlB", is_avl(avlA));
	printf("\n");
}

void test_avlds_merge() {
	printf("------------------\n");
	printf("Test: avlds_merge\n\n");
	int n = sizeof testsA / sizeof *testsA;
	for (int i = 0; i < n; i++) {
		add_record(&avldsA, testsA[i]);
	}
	printf("%s(%s): ", "display_stats", "avldsA");
	display_stats(&avldsA);
	printf("\n");

	n = sizeof testsB / sizeof *testsB;
	for (int i = n - 1; i >= 0; i--) {
		add_record(&avldsB, testsB[i]);
	}
	printf("%s(%s): ", "display_stats", "avldsB");
	display_stats(&avldsB);
	printf("\n");

	n = sizeof testsC / sizeof *testsC;
	for (int i = n - 1; i >= 0; i--) {
		add_record(&avldsC, testsC[i]);
	}
	printf("%s(%s): ", "display_stats", "avldsC");
	display_stats(&avldsC);
	printf("\n");

	avlds_merge(&avldsA, &avldsB);
	printf("%s(%s %s)-", "avlds_merge", "avldsA", "avldsB");
	printf("%s(%s): ", "display_stats", "avldsA");
	display_stats(&avldsA);
	printf("\n");
	printf("%s: %d\n", "avldsA.count", avldsA.count);
	printf("%s: %.1f\n", "avldsA.mean", avldsA.mean);
	printf("%s: %.1f\n", "avldsA.stddev", avldsA.stddev);

	printf("%s: %d\n", "avldsB.count", avldsB.count);
	printf("%s: %.1f\n", "avldsB.mean", avldsB.mean);

	printf("%s==%s: %d\n", "avldsA.count", "avldsC.count",
			avldsA.count == avldsC.count);
	printf("%s==%s: %d\n", "avldsA.mean", "avldsC.mean",
			fabs(avldsA.mean - avldsC.mean) < EPSILON);
	printf("%s==%s: %d\n", "avldsA.stddev", "avldsC.stddev",
			fabs(avldsA.stddev - avldsC.stddev) < EPSILON);

	avlds_clean(&avldsA);
	avlds_clean(&avldsB);
	avlds_clean(&avldsC);

	printf("\n");
}

int main(int argc, char* args[]) {
	test_avl_merge();
	test_avlds_merge();
	return 0;
}

void display_inorder(AVLNODE *root) {
	if (root) {
		if (root->left)
			display_inorder(root->left);
		printf("%s,%3.1f\n", root->data.name, root->data.score);
		if (root->right)
			display_inorder(root->right);
	}
}

void display_stats(const AVLDS *root) {
	printf("%s %d ", "count", root->count);
	printf("%s %.1f ", "mean", root->mean);
	printf("%s %.1f", "stddev", root->stddev);
}

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

