/**
 * -------------------------------------
 * @file  name_set_initialize.c
 * Lab 5 Source Code File
 * -------------------------------------
 * @author Heider Ali, 999999999, heali@wlu.ca
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "name_set.h"

name_set *name_set_initialize() {
	// Allocate memory to the data structure
	name_set *set = malloc(sizeof *set);
	// Initialize the header fields.
	set->front = NULL;
	set->rear = NULL;
	return set;
}

int name_set_free(name_set **set) {
	if (set == NULL || *set == NULL) {
		return 0;
	}

	name_set_node *current = (*set)->front;
	name_set_node *temp;
	int count = 0;

	// Free all nodes
	while (current != NULL) {
		temp = current;
		current = current->next;
		free(temp);
		count++;
	}

	// Free the header structure
	free(*set);
	*set = NULL;
	return count + 1; // Add 1 for the header node
}

BOOLEAN name_set_append(name_set *set, const char *first_name,
												const char *last_name) {
	if (set == NULL || first_name == NULL || last_name == NULL) {
		return FALSE;
	}

	// Check if name already exists
	if (name_set_contains(set, first_name, last_name)) {
		return FALSE;
	}

	// Create new node
	name_set_node *new_node = malloc(sizeof(name_set_node));
	if (new_node == NULL) {
		return FALSE;
	}

	// Copy names to new node
	strncpy(new_node->first_name, first_name, NAME_LEN - 1);
	new_node->first_name[NAME_LEN - 1] = '\0';
	strncpy(new_node->last_name, last_name, NAME_LEN - 1);
	new_node->last_name[NAME_LEN - 1] = '\0';
	new_node->next = NULL;

	// If list is empty
	if (set->front == NULL) {
		set->front = new_node;
		set->rear = new_node;
	} else {
		set->rear->next = new_node;
		set->rear = new_node;
	}

	return TRUE;
}

BOOLEAN name_set_contains(const name_set *set, const char *first_name,
													const char *last_name) {
	if (set == NULL || first_name == NULL || last_name == NULL) {
		return FALSE;
	}

	name_set_node *current = set->front;

	while (current != NULL) {
		if (strcmp(current->first_name, first_name) == 0 &&
				strcmp(current->last_name, last_name) == 0) {
			return TRUE;
		}
		current = current->next;
	}

	return FALSE;
}

void name_set_print(const name_set *set) {
	if (set == NULL) {
		return;
	}

	name_set_node *current = set->front;

	while (current != NULL) {
		printf("%s, %s\n", current->last_name, current->first_name);
		current = current->next;
	}
}
