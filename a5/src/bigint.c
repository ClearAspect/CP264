#include "bigint.h"
#include <stdlib.h>
#include <string.h>

BIGINT bigint(char *digitstr) {
	BIGINT bigint = {0, NULL, NULL}; // Initialize empty DLL
	int len = strlen(digitstr);

	// Process each digit from right to left
	for (int i = len - 1; i >= 0; i--) {
		if (digitstr[i] >= '0' && digitstr[i] <= '9') {
			NODE *np = dll_node(digitstr[i] - '0');
			dll_insert_start(&bigint, np);
		}
	}

	// If empty string or no valid digits, insert '0'
	if (bigint.length == 0) {
		NODE *np = dll_node(0);
		dll_insert_start(&bigint, np);
	}

	return bigint;
}

BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2) {
	BIGINT result = {0, NULL, NULL};
	NODE *p1 = oprand1.end;
	NODE *p2 = oprand2.end;
	int carry = 0;

	// Add digits from right to left
	while (p1 != NULL || p2 != NULL || carry) {
		int sum = carry;

		if (p1) {
			sum += p1->data;
			p1 = p1->prev;
		}
		if (p2) {
			sum += p2->data;
			p2 = p2->prev;
		}

		carry = sum / 10;
		sum = sum % 10;

		NODE *np = dll_node(sum);
		dll_insert_start(&result, np);
	}

	return result;
}

BIGINT bigint_fibonacci(int n) {
	if (n <= 0) {
		return bigint("0");
	}
	if (n == 1) {
		return bigint("1");
	}

	BIGINT fib1 = bigint("0");
	BIGINT fib2 = bigint("1");
	BIGINT result;

	for (int i = 2; i <= n; i++) {
		result = bigint_add(fib1, fib2);
		dll_clean(&fib1);
		fib1 = fib2;
		fib2 = result;
	}

	return result;
}
