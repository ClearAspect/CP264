/**
 * Use selection sort algorithm to sort array of pointers such that their pointed values 
 * are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 */
void select_sort(void *a[], int left, int right);

/**
 * Use quick sort algorithm to sort array of pointers such that their pointed values 
 * are in increasing order.
 *
 * @param *a[] - array of void pointers. 
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 */
void quick_sort(void *a[], int left, int right);

/**
 * Use either selection or quick sort algorithm to sort array of pointers such that their pointed values 
 * are in order defined by the given comparison function
 *
 * @param *a[] - array of void pointers. 
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 * @param (*cmp) - pointer to a comparison function used to compaire pointers by their pointed values.
 */
void my_sort(void *a[], int left, int right, int (*cmp)(void*, void*) );
