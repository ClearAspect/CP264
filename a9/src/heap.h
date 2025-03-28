#ifndef HEAP_H
#define HEAP_H

/*
 * Define KEYTYPE as int type
 */
typedef int KEYTYPE;

/*
 * Define VALUETYPE as int type
 */
typedef int VALUETYPE;

/*
 * Define structure type HEAPDATA containing
 * KEYTYPE key - used as key for heap operations
 * VALUETYPE value - associated data value.
 */
typedef struct {
	KEYTYPE key;
	VALUETYPE value;
} HEAPDATA;

/*
 * Define structure type HEAP containing
 * unsigned int size  - the number heap elements
 * unsigned int capacity - the MAX length of binary heap array
 * HEAPDATA *hda - pointer pointing the heap element array
 */
typedef struct heap {
	unsigned int size;		 //
	unsigned int capacity; // the MAX length of binary heap array
	HEAPDATA *hda;				 // pointer pointing the heap element array
} HEAP;

/* Use malloc to create HEAP type object, set its size 0, capacity 4,
 * then create an array of HEAPDATA elements of length equal to the capacity
 * and let hda point to the array. Return the pointer of the HEAP object.
 * @param capacity - the capacity of the binary heap, i.e. the length of the
 * heap array.
 * @return - pointer to the HEAP object.
 */
HEAP *new_heap(int capacity);

/* Insert the given HEAPDADA data into a heap. When the heap size is equal to
 * the capacity, expand data array by doubling its length and copy the data of
 * old array to the new array in case of need, then insert the data into the
 * heap array.
 * @param heap - pointer to the heap.
 * @param data - data to be inserted.
 */
void heap_insert(HEAP *heap, HEAPDATA data);

/* Get the HEAPDADA data of minimum key.
 * @param heap - pointer to the heap.
 * @return - the minimum key HEAPDATA
 */
HEAPDATA heap_find_min(HEAP *heap);

/* Get the minimum key HEAPDADA data and delete it from the heap.
 * When the heap->size <= (heap->capacity)/4 and heap->capacity>4, shrink the
 * HEAPDATA array by half.
 * @param heap - pointer to the heap.
 * @return - the minimum key HEAPDATA
 */
HEAPDATA heap_extract_min(HEAP *heap);

/* Changes heap->hda[index].key to new_key, heapify, return the index of new
 * position of the new_key element.
 * @param heap - pointer to the heap.
 * @param index - index of HEAPDATA for key changing.
 * @param new_kay - key value to to be changed.
 * @return - position index of the new_key element.
 */
int heap_change_key(HEAP *heap, int index, KEYTYPE new_key);

/* Find and return the index of the first HEAPDATA data such that data.value ==
 * val.
 * @param heap - pointer to the heap.
 * @param val -  match value for search.
 * @return - position index of HEAPDATA data if found, otherwise -1.
 */
int heap_search_value(HEAP *heap, VALUETYPE val);

/* Free dynamically allocated memory of the given heap, and set its pointer to
 * NULL.
 * @param heapp - pointer of pointer to the heap.
 */
void heap_clean(HEAP **heapp);

/* Sort HEAPDATA array in place in decreasig order of HEAPDATA key.
 * @param *arr - array pointer of HEAPDATA array
 * @param n - length of the input array.
 */
void heap_sort(HEAPDATA *arr, int n);

#endif // !HEAP_H
