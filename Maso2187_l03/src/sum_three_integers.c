/**
 * -------------------------------------
 * @file  functions.c
 * Lab 2 Functions Source Code File
 * -------------------------------------
 * @author Roan Mason, 169072187, Maso2187@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_three_integers(void) {

	// your code here

	int done = 0;
	int sum;
	int num1, num2, num3;
	char input[STRING_SMALL] = "";

	while (done != 1) {

		// Prompt user for input
		printf("Enter three comma-separated integers: ");
		// Read input from user
		fgets(input, STRING_SMALL, stdin);

		// Check if input is valid
		if (sscanf(input, "%d,%d,%d", &num1, &num2, &num3) == 3) {
			// If input is valid, sum the integers
			sum = num1 + num2 + num3;
			done = 1;
		} else {
			// If input is invalid, print error message
			printf("The integers were not properly entered.\n");
		}
	}

	return sum;
}
