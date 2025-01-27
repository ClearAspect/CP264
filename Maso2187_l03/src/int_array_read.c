/**
 * -------------------------------------
 * @file  int_array_read.c
 * Lab 3 Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"
#include <stdint.h>
#include <stdio.h>

void int_array_read(int *array, int size) {

	// your code here

	int validInput;
	char input[10];
	int done = 0;

	printf("Enter %d values for an array of int.\n", size);

	for (int i = 0; i < size; ++i) {
		printf("Value for index %d:", i);
		fgets(input, 10, stdin);

		if (sscanf(input, "%d", &validInput) == 1) {
			array[i] = validInput;
		} else {
			printf("Not a valid integer\n");
			--i;
		}
	}
}
