/**
 * -------------------------------------
 * @file  queue_linked.c
 * Linked Queue Source Code File
 * -------------------------------------
 * @author name, ID, email
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
// Includes
#include "queue_linked.h"
#include <stdlib.h>

// Functions

queue_linked *queue_initialize() {

	// your code here

	// Allocate memory for the queue
	queue_linked *queue = (queue_linked *)malloc(sizeof(queue_linked));

	// Failed to allocate memory
	if (queue == NULL) {
		free(queue);
		return NULL;
	}

	// Initialize the queue
	queue->front = NULL;
	queue->rear = NULL;
	queue->count = 0;

	return queue;
}

void queue_free(queue_linked **source) {

	// your code here
	if (source == NULL || *source == NULL) {
		return;
	}

	// Free all nodes
	queue_node *current = (*source)->front;
	while (current != NULL) {
		queue_node *temp = current;
		current = current->next;
		free(temp->item);
		free(temp);
	}

	// Free the queue
	free(*source);
	*source = NULL;

	return;
}

bool queue_empty(const queue_linked *source) {

	// your code here
	if (source == NULL) {
		return true;
	}

	return (source->count == 0);
}

int queue_count(const queue_linked *source) {

	// your code here
	if (source == NULL) {
		return 0;
	}

	return source->count;
}

bool queue_insert(queue_linked *source, data_ptr item) {

	// your code here

	// Check for NULL pointers
	if (source == NULL || item == NULL) {
		return false;
	}

	// Create new node & allocate memory
	queue_node *new_node = malloc(sizeof(queue_node));
	if (new_node == NULL) {
		return false;
	}

	// Allocate memory for the item
	new_node->item = malloc(sizeof(data_ptr));
	if (new_node->item == NULL) {
		free(new_node); // Failed to allocate memory
		return false;
	}

	// Copy the data
	data_copy(new_node->item, item);
	new_node->next = NULL;

	// If the queue is empty, update front pointer
	if (source->front == NULL) {
		source->front = new_node;
		source->rear = new_node;
	} else {
		source->rear->next = new_node;
		source->rear = new_node;
	}

	// Update count
	source->count++;

	return true;
}

bool queue_peek(const queue_linked *source, data_ptr item) {

	// your code here

	if (source == NULL || item == NULL || source->front == NULL) {
		return false;
	}

	// Copy the data from the front node to item
	*item = *(source->front->item);
	return true;
}

bool queue_remove(queue_linked *source, data_ptr *item) {

	// your code here

	// Check for NULL pointers and empty queue
	if (source == NULL || item == NULL || source->front == NULL) {
		return false;
	}

	// Get the front node
	queue_node *temp = source->front;
	*item = temp->item; // Transfer ownership of the data

	// Update front pointer
	source->front = temp->next;

	// If queue becomes empty, update rear pointer
	if (source->front == NULL) {
		source->rear = NULL;
	}

	source->count--;
	free(temp); // Free only the node, not the data
	return true;
}

void queue_print(const queue_linked *source) {
	char string[DATA_STRING_SIZE];
	queue_node *current = source->front;

	while (current != NULL) {
		data_string(string, sizeof string, current->item);
		printf("%s\n", string);
		current = current->next;
	}
	return;
}
