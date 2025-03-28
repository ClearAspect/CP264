/**
 * -------------------------------------
 * @file  min_heap.c
 * Minimum Heap Source Code File
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "min_heap.h"

#define STRING_SIZE 80

// local functions

/**
 * Swaps two data values.
 *
 * @param a pointer to data.
 * @param b pointer to data.
 */
static void heap_swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;
}

/**
 * Moves the last value in source until it is in its correct location
 * in source.
 *
 * @param source - pointer to a heap
 */
static void heapify_up(min_heap *source) {
	// Get the index of the last item in the heap
	int index = source->count - 1;
	int parent_index;

	// While we haven't reached the root and parent is greater than current
	while (index > 0) {
		// Calculate parent index
		parent_index = (index - 1) / 2;

		// If parent is smaller or equal, heap property is satisfied
		if (source->values[parent_index] <= source->values[index]) {
			break;
		}

		// Swap current value with parent
		heap_swap(&source->values[index], &source->values[parent_index]);

		// Move up to parent index
		index = parent_index;
	}

	return;
}

/**
 * Moves a value down source to its correct position.
 *
 * @param source - pointer to a heap
 */
static void heapify_down(min_heap *source) {
	int index = 0; // Start from the root
	int left_child, right_child, min_child;

	// Continue until we reach a leaf node
	while (1) {
		// Calculate indices of children
		left_child = 2 * index + 1;
		right_child = 2 * index + 2;

		// If we have no children, we're done
		if (left_child >= source->count) {
			break;
		}

		// Find the smaller child
		min_child = left_child;
		if (right_child < source->count &&
				source->values[right_child] < source->values[left_child]) {
			min_child = right_child;
		}

		// If current value is already smaller than the smallest child, we're done
		if (source->values[index] <= source->values[min_child]) {
			break;
		}

		// Swap with the smaller child
		heap_swap(&source->values[index], &source->values[min_child]);

		// Move down to the child position
		index = min_child;
	}

	return;
}

// Public minimum heap functions

min_heap *min_heap_initialize(int capacity) {
	min_heap *source = malloc(sizeof *source);
	source->values = malloc(capacity * sizeof *source->values);
	source->capacity = capacity;
	source->count = 0;
	return source;
}

void min_heap_free(min_heap **source) {
	free((*source)->values);
	free(*source);
	*source = NULL;
	return;
}

void min_heap_heapify(min_heap *source, int *keys, int count) {

	for (int i = 0; i < count; i++) {
		min_heap_insert(source, keys[i]);
	}
	return;
}

int min_heap_empty(const min_heap *source) {
	return (source->count == 0);
}

int min_heap_full(const min_heap *source) {
	return (source->count == source->capacity);
}

int min_heap_count(const min_heap *source) {
	return (source->count);
}

void min_heap_insert(min_heap *source, const int value) {
	// Add new value to end of the heap.
	source->values[source->count] = value;
	source->count++;
	// Fix the heap.
	heapify_up(source);
	return;
}

int min_heap_peek(const min_heap *source) {
	return (source->values[0]);
}

int min_heap_remove(min_heap *source) {
	int value = source->values[0];
	source->count--;

	if (source->count > 0) {
		// Move last value to top of heap.
		source->values[0] = source->values[source->count];
		// Fix the heap.
		heapify_down(source);
	}
	return value;
}

int min_heap_valid(const min_heap *source) {
	// Empty heap is valid
	if (source->count <= 1) {
		return 1;
	}

	// Check each node with its children
	for (int i = 0; i < source->count / 2; i++) {
		int left_child = 2 * i + 1;
		int right_child = 2 * i + 2;

		// Check left child if it exists
		if (left_child < source->count &&
				source->values[i] > source->values[left_child]) {
			return 0; // Invalid: parent is greater than left child
		}

		// Check right child if it exists
		if (right_child < source->count &&
				source->values[i] > source->values[right_child]) {
			return 0; // Invalid: parent is greater than right child
		}
	}

	return 1; // All nodes checked, heap is valid
}

int min_heap_replace(min_heap *source, int replacement) {
	int value = source->values[0];
	source->values[0] = replacement;
	heapify_down(source);
	return value;
}

void heap_sort(int *values, int count) {
	// Create a new heap
	min_heap *heap = min_heap_initialize(count);

	// Insert all values into the heap
	for (int i = 0; i < count; i++) {
		min_heap_insert(heap, values[i]);
	}

	// Extract all values in sorted order
	for (int i = 0; i < count; i++) {
		values[i] = min_heap_remove(heap);
	}

	// Free the heap
	min_heap_free(&heap);

	return;
}

// for testing
void min_heap_print(const min_heap *source) {
	printf("{");

	for (int i = 0; i < source->count; i++) {
		printf("%d, ", source->values[i]);
	}
	printf("}\n");
	return;
}
