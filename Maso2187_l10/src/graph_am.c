/**
 * -------------------------------------
 * @file  graph_am.c
 * Adjacency Matrix Graph Code File
 * -------------------------------------
 * @author Roan Mason, 169072187, Maso2187@mylaurier.ca
 *
 * @version 2025-01-06
 *
 * -------------------------------------
 */
#include "graph_am.h"

// Initializes an adjacency matrix graph.
graph_am *graph_am_initialize(int size) {
	graph_am *source = malloc(sizeof *source);
	source->size = size;
	// Initialize values to zeroes.
	source->values = calloc(size * size, sizeof *source->values);
	return source;
}

void graph_am_free(graph_am **source) {
	// Free up the data array.
	free((*source)->values);
	(*source)->values = NULL;
	free(*source);
	*source = NULL;
	return;
}

int graph_am_add_vertice(graph_am *source, const graph_am_pair *pair) {
	int added = 0;

	// your code here

	// Check for null pointers and invalid indices
	if (source == NULL || pair == NULL) {
		return added;
	}

	// Check if row and column are within valid range
	if (pair->row < 0 || pair->row >= source->size || pair->col < 0 ||
		pair->col >= source->size) {
		return added;
	}

	// Calculate positions in the 1D array (row-major order)
	int pos = pair->row * source->size + pair->col;
	int symmetric_pos = pair->col * source->size + pair->row;

	// Only add if the position is currently empty (0)
	if (source->values[pos] == 0) {
		// Self-loop case
		if (pair->row == pair->col) {
			source->values[pos] = 2;
		} else {
			// Regular case - set both positions for symmetry
			source->values[pos] = 1;
			source->values[symmetric_pos] = 1;
		}
		added = 1;
	}

	return added;
}

int graph_am_remove_vertice(graph_am *source, const graph_am_pair *pair) {
	int removed = 0;

	// your code here

	// Check for null pointers and invalid indices
	if (source == NULL || pair == NULL) {
		return removed;
	}

	// Check if row and column are within valid range
	if (pair->row < 0 || pair->row >= source->size || pair->col < 0 ||
		pair->col >= source->size) {
		return removed;
	}

	// Calculate positions in the 1D array (row-major order)
	int pos = pair->row * source->size + pair->col;
	int symmetric_pos = pair->col * source->size + pair->row;

	// Only add if the position is currently empty (0)
	if (source->values[pos] != 0) {
		// Self-loop case
		if (pair->row == pair->col) {
			if (source->values[pos] == 2) {
				source->values[pos] = 0;
				removed = 1;
			}
		} else {
			// Regular case - set both positions for symmetry
			source->values[pos] = 0;
			source->values[symmetric_pos] = 0;
			removed = 1;
		}
	}

	return removed;
}

graph_am *graph_am_create(int size, const graph_am_pair pairs[], int count) {
	graph_am *source = graph_am_initialize(size);

	// your code here

	// Check if the input parameters are valid
	if (pairs == NULL || count <= 0) {
		return source;
	}

	// Process each pair and add it to the graph
	for (int i = 0; i < count; i++) {
		graph_am_add_vertice(source, &pairs[i]);
	}

	return source;
}

void graph_am_neighbours(const graph_am *source, int vertex, int vertices[],
						 int *count) {

	// your code here

	// Initialize count to 0
	*count = 0;

	// Check for null pointer and invalid vertex
	if (source == NULL || vertex < 0 || vertex >= source->size ||
		vertices == NULL) {
		return;
	}

	// Check each possible connection in the vertex's row
	for (int i = 0; i < source->size; i++) {
		// Calculate position in the 1D array (row-major order)
		int pos = vertex * source->size + i;

		// If there's a connection (value 1 or 2), add to neighbours
		if (source->values[pos] > 0) {
			vertices[*count] = i;
			(*count)++;
		}
	}

	return;
}

int graph_am_degree(const graph_am *source, int vertex) {
	int connected = 0;

	// your code here

	// Check for null pointer and invalid vertex
	if (source == NULL || vertex < 0 || vertex >= source->size) {
		return connected;
	}

	// Count connections in the vertex's row
	for (int i = 0; i < source->size; i++) {
		int pos = vertex * source->size + i;
		if (source->values[pos] > 0) {
			connected += *(source->values + pos);
		}
	}

	return connected;
}

void graph_am_breadth_traversal(const graph_am *source, int vertex,
								int vertices[], int *count) {

	// your code here

	*count = 0;

	// Check for null pointers and invalid vertex
	if (source == NULL || vertices == NULL || vertex < 0 ||
		vertex >= source->size) {
		return;
	}

	// Create visited array and queue
	int *visited = calloc(source->size, sizeof(int));
	int *queue = malloc(source->size * sizeof(int));
	int front = 0, rear = 0;

	// Start BFT from the given vertex
	visited[vertex] = 1;
	queue[rear++] = vertex;
	vertices[(*count)++] = vertex;

	while (front < rear) {
		int current = queue[front++];

		// Visit all unvisited neighbors
		for (int i = 0; i < source->size; i++) {
			int pos = current * source->size + i;
			if (source->values[pos] > 0 && !visited[i]) {
				visited[i] = 1;
				queue[rear++] = i;
				vertices[(*count)++] = i;
			}
		}
	}

	// Free temporary arrays
	free(visited);
	free(queue);
	return;
}

void graph_am_depth_traversal(const graph_am *source, int vertex,
							  int vertices[], int *count) {

	// your code here

	// Check for null pointers and invalid vertex
	if (source == NULL || vertices == NULL || vertex < 0 ||
		vertex >= source->size) {
		*count = 0;
		return;
	}

	// Create visited array
	int *visited = calloc(source->size, sizeof(int));
	if (visited == NULL) {
		*count = 0;
		return;
	}

	// Initialize count
	*count = 0;

	int stack[source->size];
	int top = -1;

	// Push initial vertex
	stack[++top] = vertex;

	while (top >= 0) {
		int current = stack[top--];

		if (!visited[current]) {
			visited[current] = 1;
			vertices[(*count)++] = current;

			// We want to visit 2 before 1, so we need to push 1 first (LIFO)
			for (int i = 0; i < source->size; i++) {
				int pos = current * source->size + i;
				if (!visited[i] && source->values[pos] > 0) {
					stack[++top] = i;
				}
			}
		}
	}

	// Free visited array
	free(visited);
	return;
}

// Prints the contents of an adjacency matrix graph.
void graph_am_print(const graph_am *source) {
	// Print the column numbers.
	printf("    ");

	for (int i = 0; i < source->size; i++)
		printf("%3d", i);
	printf("\n");
	printf("    ");
	for (int i = 0; i < source->size; i++)
		printf("---");
	printf("\n");

	// Print the row numbers and rows.
	for (int i = 0; i < source->size; i++) {
		printf("%3d|", i);

		for (int j = 0; j < source->size; j++) {
			// find item using offsets
			printf("%3d", *(source->values + i * source->size + j));
		}
		printf("\n");
	}
}
