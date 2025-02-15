#include "mysort.h"

// swap pointers
void swap(void **x, void **y) {
	void *temp = *y;
	*y = *x;
	*x = temp;
}

// a compare floating values pointed by void pointers.
int cmp(void *x, void *y) {
	float a = *(float *)x;
	float b = *(float *)y;
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

void select_sort(void *a[], int left, int right) {
	// selection sort
	for (int i = left; i <= right; ++i) {
		int minIndex = i;
		// find the index of the smallest element in the array
		for (int j = i + 1; j <= right; ++j) {
			if (cmp(a[j], a[minIndex]) < 0) {
				minIndex = j;
			}
		}

		if (i != minIndex) { // the following swap a[i] and a[minIndex]
			swap(&a[i], &a[minIndex]);
		}
	}
}

int partition(void *a[], int low, int high) {

	// Choose the pivot
	void *pivot = a[high];

	// index of the smaller element that
	// indicates the right position of the pivot
	int i = low - 1;

	// Traverse the array
	// move all the smaller elements to the left of the pivot
	// element and the greater elements to the right
	for (int j = low; j <= high - 1; ++j) {
		if (cmp(a[j], pivot) < 0) {
			// if the pivot is greater than the current element
			// move the current element to the left of the pivot
			++i;
			swap(&a[i], &a[j]);
		}
	}

	// move the pivot element to the postition after the smaller elements and
	// return this postition
	swap(&a[i + 1], &a[high]);
	return i + 1;
}

void quick_sort(void *a[], int left, int right) {

	if (left < right) {

		// the partition is the index of the next pivot
		int pivot = partition(a, left, right);

		// recursively sort subarrays
		quick_sort(a, left, pivot - 1);
		quick_sort(a, pivot + 1, right);
	}
}

void my_sort(void *a[], int left, int right, int (*cmp)(void *, void *)) {

	// selection sort
	for (int i = left; i <= right; ++i) {
		int k = i;
		// find the index of the smallest element in the array
		for (int j = i + 1; j <= right; ++j) {
			if ((*cmp)(a[j], a[k]) < 0) {
				k = j;
			}
		}
		if (i != k) { // the following swap a[i] and a[k]
			swap(&a[i], &a[k]);
		}
	}

	return;
}
