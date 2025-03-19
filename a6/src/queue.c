#include "queue.h"

#include <stdlib.h>

void enqueue(QUEUE *qp, NODE *np) {
	// Check if the queue and node aren't NULL pointers
	if (qp == NULL || np == NULL)
		return;

	// Ensure the new node doesn't point to anything
	np->next = NULL;

	// If the queue is empty, set the front and rear to the new node
	if (qp->front == NULL) {
		// Empty
		qp->front = np;
		qp->rear = np;
	} else {
		// Otherwise, add the new node to the rear of the queue
		qp->rear->next = np;
		qp->rear = np;
	}

	qp->length++; // Increase the length of the queue
	return;
}

NODE *dequeue(QUEUE *qp) {
	// Check if the queue is empty
	if (qp == NULL || qp->front == NULL)
		return NULL;

	// Get the front node
	NODE *np = qp->front;

	// Move the front pointer to the next node
	qp->front = qp->front->next;

	// Check if the queue is now empty
	if (qp->front == NULL) {
		qp->rear = NULL;
	}

	// Set the removed node's next to NULL
	np->next = NULL;
	// Decrease the length of the queue
	qp->length--;

	return np;
}

void clean_queue(QUEUE *qp) {
	// Check if the queue is NULL
	if (qp == NULL)
		return;

	// Get the front node
	NODE *current = qp->front;
	// Temporary node
	NODE *temp;

	// Free all nodes
	while (current != NULL) {
		temp = current;
		current = current->next;
		free(temp);
	}

	// Reset queue properties
	qp->front = NULL;
	qp->rear = NULL;
	qp->length = 0;
	return;
}
