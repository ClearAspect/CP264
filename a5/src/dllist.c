#include "dllist.h"
#include <stdlib.h>

NODE *dll_node(char value) {
	// Initialize a new node
	NODE *new_node = (NODE *)malloc(sizeof(NODE));
	if (new_node == NULL)
		return NULL;

	// Initialize node values
	new_node->data = value;
	new_node->next = NULL;
	new_node->prev = NULL;

	return new_node;
}

void dll_insert_start(DLL *dllp, NODE *np) {
	if (dllp == NULL || np == NULL)
		return;

	// Set new node's links
	np->next = dllp->start;
	np->prev = NULL;

	// If list is not empty, update previous start node
	if (dllp->start != NULL) {
		dllp->start->prev = np;
	} else {
		// If list was empty, new node is also the end
		dllp->end = np;
	}

	// Update list
	dllp->start = np;
	dllp->length++;
}

void dll_insert_end(DLL *dllp, NODE *np) {
	if (dllp == NULL || np == NULL)
		return;

	// Set new node's links
	np->next = NULL;
	np->prev = dllp->end;

	// If list is not empty, update current end node
	if (dllp->end != NULL) {
		dllp->end->next = np;
	} else {
		// If list was empty, new node is also the start
		dllp->start = np;
	}

	// Update list
	dllp->end = np;
	dllp->length++;
}

void dll_delete_start(DLL *dllp) {
	if (dllp == NULL || dllp->start == NULL)
		return;

	NODE *temp = dllp->start;

	// Update start to point to second node
	dllp->start = temp->next;

	// If there was only one node, update end to NULL
	if (dllp->start == NULL) {
		dllp->end = NULL;
	} else {
		// Otherwise, update new start node's prev pointer
		dllp->start->prev = NULL;
	}

	// Free the removed node and update length
	free(temp);
	dllp->length--;
}

void dll_delete_end(DLL *dllp) {
	if (dllp == NULL || dllp->end == NULL)
		return;

	NODE *temp = dllp->end;

	// Update end to point to second-to-last node
	dllp->end = temp->prev;

	// If there was only one node, update start to NULL
	if (dllp->end == NULL) {
		dllp->start = NULL;
	} else {
		// Otherwise, update new end node's next pointer
		dllp->end->next = NULL;
	}

	// Free the removed node and update length
	free(temp);
	dllp->length--;
}

void dll_clean(DLL *dllp) {
	if (dllp == NULL)
		return;

	NODE *current = dllp->start;
	NODE *next;

	// Traverse the list, freeing each node
	while (current != NULL) {
		next = current->next;
		free(current);
		current = next;
	}

	// Reset list properties
	dllp->start = NULL;
	dllp->end = NULL;
	dllp->length = 0;
}
