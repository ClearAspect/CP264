#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash(char *key, int size) {
	int hash_value = 0;
	while (*key) {
		hash_value += *key;
		key++;
	}
	return hash_value % size;
}

HASHTABLE *new_hashtable(int size) {
	HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));
	if (ht == NULL)
		return NULL;

	ht->size = size;
	ht->count = 0;
	ht->hna = (HNODE **)malloc(sizeof(HNODE *) * size);

	if (ht->hna == NULL) {
		free(ht);
		return NULL;
	}

	// Initialize all buckets to NULL
	for (int i = 0; i < size; i++) {
		ht->hna[i] = NULL;
	}

	return ht;
}

int hashtable_insert(HASHTABLE *ht, DATA data) {
	if (ht == NULL)
		return 0;

	// Get hash value for the key
	int index = hash(data.name, ht->size);

	// Check if the key already exists
	HNODE *current = ht->hna[index];
	while (current != NULL) {
		if (strcmp(current->data.name, data.name) == 0) {
			// Key exists, update value
			current->data.value = data.value;
			return 0; // Return 0 for update
		}
		current = current->next;
	}

	// Key doesn't exist, create new node
	HNODE *new_node = (HNODE *)malloc(sizeof(HNODE));
	if (new_node == NULL)
		return 0;

	// Copy data to the new node
	new_node->data = data;

	// Insert at the beginning of the linked list
	new_node->next = ht->hna[index];
	ht->hna[index] = new_node;

	// Increment count
	ht->count++;

	return 1; // Return 1 for insert
}

HNODE *hashtable_search(HASHTABLE *ht, char *name) {
	if (ht == NULL || name == NULL)
		return NULL;

	// Get hash value for the key
	int index = hash(name, ht->size);

	// Search for the key in the linked list
	HNODE *current = ht->hna[index];
	while (current != NULL) {
		if (strcmp(current->data.name, name) == 0) {
			return current; // Return pointer to the found node
		}
		current = current->next;
	}

	return NULL; // Key not found
}

int hashtable_delete(HASHTABLE *ht, char *key) {
	if (ht == NULL || key == NULL)
		return 0;

	// Get hash value for the key
	int index = hash(key, ht->size);

	HNODE *current = ht->hna[index];
	HNODE *previous = NULL;

	// Search for the key in the linked list
	while (current != NULL) {
		if (strcmp(current->data.name, key) == 0) {
			// Found the key to delete

			// Adjust pointers to remove the node
			if (previous == NULL) {
				// Deleting the first node in the list
				ht->hna[index] = current->next;
			} else {
				// Deleting a node in the middle or end
				previous->next = current->next;
			}

			// Free the memory and decrement count
			free(current);
			ht->count--;

			return 1; // Return 1 for successful deletion
		}

		previous = current;
		current = current->next;
	}

	return 0; // Key not found
}

void hashtable_clean(HASHTABLE **ht) {
	if (ht == NULL || *ht == NULL)
		return;

	HASHTABLE *table = *ht;

	// Free all nodes in each bucket
	for (int i = 0; i < table->size; i++) {
		HNODE *current = table->hna[i];
		while (current != NULL) {
			HNODE *temp = current;
			current = current->next;
			free(temp);
		}
		table->hna[i] = NULL;
	}

	// Reset count
	table->count = 0;

	// Note: This doesn't free the hashtable itself,
	// it just cleans all the linked lists and resets the count
}
