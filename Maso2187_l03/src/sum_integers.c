/**
 * -------------------------------------
 * @file  sum_integers.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author Roan Mason, 169072187, Maso2187@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_integers(void) {

	// your code here

	int input = 0;
	int sum = 0;
	int scan_result;

	printf("Enter integers, one per line:\n");

	while ((scan_result = scanf("%d", &input)) == 1) {
		sum += input;
	}

	return sum;
}
