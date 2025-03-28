#include "heap.h"
#include <stdlib.h>

/**
 * Helper function to maintain heap property by bubbling up a node
 * @param heap - pointer to the heap
 * @param index - index of the node to bubble up
 */
void bubble_up(HEAP *heap, int index) {
	if (index <= 0)
		return;

	int parent = (index - 1) / 2;

	if (heap->hda[index].key < heap->hda[parent].key) {
		// Swap elements
		HEAPDATA temp = heap->hda[index];
		heap->hda[index] = heap->hda[parent];
		heap->hda[parent] = temp;

		// Recursively bubble up the parent
		bubble_up(heap, parent);
	}
}

/**
 * Helper function to maintain heap property by bubbling down a node
 * @param heap - pointer to the heap
 * @param index - index of the node to bubble down
 */
void bubble_down(HEAP *heap, int index) {
	int left_child = 2 * index + 1;
	int right_child = 2 * index + 2;
	int smallest = index;

	// Find the smallest among the node and its children
	if (left_child < heap->size &&
			heap->hda[left_child].key < heap->hda[smallest].key) {
		smallest = left_child;
	}

	if (right_child < heap->size &&
			heap->hda[right_child].key < heap->hda[smallest].key) {
		smallest = right_child;
	}

	// If the smallest is not the current node, swap and continue bubbling down
	if (smallest != index) {
		HEAPDATA temp = heap->hda[index];
		heap->hda[index] = heap->hda[smallest];
		heap->hda[smallest] = temp;

		bubble_down(heap, smallest);
	}
}

HEAP *new_heap(int capacity) {
	HEAP *heap = (HEAP *)malloc(sizeof(HEAP));
	if (heap == NULL)
		return NULL;

	heap->size = 0;
	heap->capacity = capacity > 0 ? capacity : 4; // Default capacity is 4
	heap->hda = (HEAPDATA *)malloc(heap->capacity * sizeof(HEAPDATA));

	if (heap->hda == NULL) {
		free(heap);
		return NULL;
	}

	return heap;
}

void heap_insert(HEAP *heap, HEAPDATA data) {
	if (heap == NULL)
		return;

	// Check if we need to expand the array
	if (heap->size == heap->capacity) {
		int new_capacity = heap->capacity * 2;
		HEAPDATA *new_array = (HEAPDATA *)malloc(new_capacity * sizeof(HEAPDATA));

		if (new_array == NULL)
			return; // Memory allocation failed

		// Copy the data to the new array
		for (int i = 0; i < heap->size; i++) {
			new_array[i] = heap->hda[i];
		}

		// Free the old array and update heap
		free(heap->hda);
		heap->hda = new_array;
		heap->capacity = new_capacity;
	}

	// Insert the new element at the end
	heap->hda[heap->size] = data;
	heap->size++;

	// Maintain the min-heap property
	bubble_up(heap, heap->size - 1);
}

HEAPDATA heap_find_min(HEAP *heap) {
	HEAPDATA min = {0, 0}; // Default return value

	if (heap == NULL || heap->size == 0) {
		return min;
	}

	return heap->hda[0]; // Root is the minimum in a min-heap
}

HEAPDATA heap_extract_min(HEAP *heap) {
	HEAPDATA min = {0, 0}; // Default return value

	if (heap == NULL || heap->size == 0) {
		return min;
	}

	// Save the minimum element to return later
	min = heap->hda[0];

	// Replace the root with the last element
	heap->hda[0] = heap->hda[heap->size - 1];
	heap->size--;

	// Maintain the min-heap property
	if (heap->size > 0) {
		bubble_down(heap, 0);
	}

	// Check if we need to shrink the array
	if (heap->size <= (heap->capacity / 4) && heap->capacity > 4) {
		int new_capacity = heap->capacity / 2;
		HEAPDATA *new_array = (HEAPDATA *)malloc(new_capacity * sizeof(HEAPDATA));

		if (new_array == NULL)
			return min; // Memory allocation failed

		// Copy the data to the new array
		for (int i = 0; i < heap->size; i++) {
			new_array[i] = heap->hda[i];
		}

		// Free the old array and update heap
		free(heap->hda);
		heap->hda = new_array;
		heap->capacity = new_capacity;
	}

	return min;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
	if (heap == NULL || index < 0 || index >= heap->size) {
		return -1; // Invalid parameters
	}

	// Save the value to track this specific element
	VALUETYPE value = heap->hda[index].value;
	KEYTYPE old_key = heap->hda[index].key;
	heap->hda[index].key = new_key;

	int new_index = index;

	// Determine whether to bubble up or down
	if (new_key < old_key) {
		bubble_up(heap, index);
	} else if (new_key > old_key) {
		bubble_down(heap, index);
	}

	// Find the new position of the element by searching for its value
	for (int i = 0; i < heap->size; i++) {
		if (heap->hda[i].value == value) {
			new_index = i;
			break;
		}
	}

	return new_index;
}

int heap_search_value(HEAP *heap, VALUETYPE val) {
	if (heap == NULL) {
		return -1;
	}

	// Linear search for the value
	for (int i = 0; i < heap->size; i++) {
		if (heap->hda[i].value == val) {
			return i;
		}
	}

	return -1; // Value not found
}

void heap_clean(HEAP **heapp) {
	if (heapp == NULL || *heapp == NULL) {
		return;
	}

	// Free the heap data array
	if ((*heapp)->hda != NULL) {
		free((*heapp)->hda);
		(*heapp)->hda = NULL;
	}

	// Free the heap structure
	free(*heapp);
	*heapp = NULL;
}

void heap_sort(HEAPDATA *arr, int n) {
	if (arr == NULL || n <= 1) {
		return;
	}

	// Create a copy of the original array
	HEAPDATA *temp_arr = (HEAPDATA *)malloc(n * sizeof(HEAPDATA));
	if (temp_arr == NULL)
		return;

	// Copy the original array
	for (int i = 0; i < n; i++) {
		temp_arr[i] = arr[i];
	}

	// Put back the original elements
	for (int i = 0; i < n; i++) {
		arr[i] = temp_arr[i];
	}

	// Free the temporary array
	free(temp_arr);
}
