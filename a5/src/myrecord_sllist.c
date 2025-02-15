#include "myrecord_sllist.h"
#include <stdlib.h>
#include <string.h>

NODE *sll_search(SLL *sllp, char *name) {

	// Check if the singly linked list and the key are not NULL
	if (sllp == NULL || name == NULL) {
		return NULL;
	}

	NODE *current = sllp->start;

	// Check if the start node is NULL
	if (current == NULL) {
		return NULL;
	}

	while (current != NULL) {
		// While the next node exists

		if (strcmp(current->data.name, name) == 0) {
			// Check the the data of the current node matches the key
			return current;
		}

		current = current->next;
	}

	return NULL;
}

void sll_insert(SLL *sllp, char *name, float score) {
	// Check if the singly linked list is not NULL
	if (sllp == NULL) {
		return;
	}

	// Create new node
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	if (new_node == NULL)
		return; // Check allocation success

	// Insert data directly into node's record
	strncpy(new_node->data.name, name, sizeof(new_node->data.name) - 1);
	new_node->data.name[sizeof(new_node->data.name) - 1] = '\0';
	new_node->data.score = score;

	//
	// Handle insertion in sorted order
	//
	NODE *current = sllp->start;
	NODE *prev = NULL;

	// Find insertion point
	while (current != NULL && strcmp(current->data.name, name) < 0) {
		prev = current;
		current = current->next;
	}

	// Insert node
	if (prev == NULL) {
		// Insert at start
		new_node->next = sllp->start;
		sllp->start = new_node;
	} else {
		// Insert after prev
		new_node->next = current;
		prev->next = new_node;
	}

	// Increment length
	sllp->length++;
}

int sll_delete(SLL *sllp, char *name) {
	// Check for null parameters
	if (sllp == NULL || name == NULL) {
		return 0;
	}

	NODE *current = sllp->start;
	NODE *prev = NULL;

	// Empty list check
	if (current == NULL) {
		return 0;
	}

	// Search for the node to delete
	while (current != NULL && strcmp(current->data.name, name) != 0) {
		prev = current;
		current = current->next;
	}

	// Node not found
	if (current == NULL) {
		return 0;
	}

	// Update the list links
	if (prev == NULL) {
		// Deleting first node
		sllp->start = current->next;
	} else {
		// Deleting node from middle or end
		prev->next = current->next;
	}

	// Free the node and decrease length
	free(current);
	sllp->length--;

	return 1;
}

void sll_clean(SLL *sllp) {
	// Check if list is NULL
	if (sllp == NULL) {
		return;
	}

	NODE *current = sllp->start;
	NODE *next;

	// Traverse the list, freeing each node
	while (current != NULL) {
		next = current->next; // Save next node before freeing current
		free(current);				// Free current node
		current = next;				// Move to next node
	}

	// Reset list properties
	sllp->start = NULL;
	sllp->length = 0;
}
