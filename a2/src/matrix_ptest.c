/*
 --------------------------------------------------
 Project: a2q3
 File:    matrix_ptest.c
 About:   public test driver
 Author:  HBF
 Version: 2025-01-14
 --------------------------------------------------
 */

#include<stdio.h>
#include "matrix.h"

char *fm ="%.1f";  //format string for float number

void display_vector(char *name, float *v, int n) {
	printf("%s:\n", name);
	for (int i = 0; i < n; i++) {
		printf(fm, v[i]);
		printf("\n");
	}
	printf("\n");
}

void display_matrix(char *name, float *m, int n) {
	printf("%s:\n", name);
	float *p = m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf(fm, *(p + i * n + j));
			printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

void test_norm() {
	printf("------------------\n");
	printf("Test: norm\n\n");
	float v1[] = { 1, 2, 2 };
	int n = sizeof(v1) / sizeof(float);
	display_vector("v1", v1, n);
	printf("norm(%s): ", "v1");
	printf(fm, norm(v1, n));
	printf("\n");
}

void test_dot_product() {
	printf("------------------\n");
	printf("Test: dot_product\n\n");
	float v1[] = { 1, 1, 1 };
	float v2[] = { 1, 2, 3 };
	int n = sizeof(v1) / sizeof(float);
	display_vector("v1", v1, n);
	display_vector("v2", v2, n);
	printf("dot_product(%s %s): ", "v1", "v2");
	printf(fm, dot_product(v1, v2, n));
	printf("\n");
}

void test_matrix_multiply_vector() {
	printf("------------------\n");
	printf("Test: matrix_multiply_vector\n\n");
	int n = 3;
	float v[] = { 1, 1, 1 };
	float m[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	display_matrix("m", m, n);
	display_vector("v", v, n);

	float v1[n];
	matrix_multiply_vector(m, v, v1, n);
	printf("matrix_multiply_vector(%s %s %s)\n", "m", "v", "v1");
	display_vector("v1", v1, n);
	printf("\n");
}

void test_matrix_multiply_matrix() {
	printf("------------------\n");
	printf("Test: matrix_multiply_matrix\n\n");
	int n = 3;
	float m1[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	float m2[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9  };
	float m3[9] = { 0 };
	display_matrix("m1", m1, n);
	display_matrix("m2", m2, n);
	matrix_multiply_matrix(m1, m2, m3, 3);
	printf("matrix_multiply_matrix(%s %s %s)\n", "m1", "m2", "m3");
	display_matrix("m3", m3, n);
	printf("\n");
}

int main() {
	test_norm();
	test_dot_product();
	test_matrix_multiply_vector();
	test_matrix_multiply_matrix();
	return 0;
}
