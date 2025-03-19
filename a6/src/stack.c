
#include "stack.h"
#include "common.h"
#include <stdlib.h>

void push(STACK *sp, NODE *np) {
	// Check for NULL pointers
	if (sp == NULL || np == NULL)
		return;

	// Set the new node's next to point to the current top node
	np->next = sp->top;

	// Update the top pointer to the new node
	sp->top = np;

	// Increment the stack length
	sp->length++;
}

NODE *pop(STACK *sp) {
	NODE *np = NULL;

	// Check if the stack exists and is not empty
	if (sp == NULL || sp->top == NULL)
		return np;

	// Get the top node
	np = sp->top;

	// Update the top pointer to the next node
	sp->top = np->next;

	// Set the popped node's next to NULL
	np->next = NULL;

	// Decrement the stack length
	sp->length--;

	return np;
}

void clean_stack(STACK *sp) {
	// Check for NULL pointer
	if (sp == NULL)
		return;

	// Declare pointers for traversal and temporary storage
	NODE *temp;

	// Traverse the stack and free each node
	while (sp->top != NULL) {
		temp = sp->top;				// Get the top node
		sp->top = temp->next; // Move top to the next node
		free(temp);						// Free the node directly
	}

	// Reset stack properties
	sp->top = NULL;
	sp->length = 0;
}
