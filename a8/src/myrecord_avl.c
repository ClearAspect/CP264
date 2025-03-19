#include "myrecord_avl.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to traverse source tree and insert nodes into destination
// tree
void traversal_insert(AVLNODE **rootp_dest, AVLNODE *root_source) {
	if (root_source) {
		avl_insert(rootp_dest, root_source->data);
		traversal_insert(rootp_dest, root_source->left);
		traversal_insert(rootp_dest, root_source->right);
	}
}

void avl_merge(AVLNODE **rootp_dest, AVLNODE **rootp_source) {
	if (rootp_source == NULL || *rootp_source == NULL)
		return;

	// Traverse the source tree and insert each node into destination tree
	traversal_insert(rootp_dest, *rootp_source);
}

// Helper function to traverse and accumulate statistics
void traverse_stats(AVLNODE *node, float *sum, float *sum_squares) {
	if (node) {
		*sum += node->data.score;
		*sum_squares += node->data.score * node->data.score;
		traverse_stats(node->left, sum, sum_squares);
		traverse_stats(node->right, sum, sum_squares);
	}
}

// Recalculate statistics for an AVLDS
void recalculate_stats(AVLDS *ds) {
	if (ds == NULL || ds->root == NULL) {
		ds->mean = 0;
		ds->stddev = 0;
		return;
	}

	// For recalculation, we need to traverse the tree
	float sum = 0;
	float sum_squares = 0;

	traverse_stats(ds->root, &sum, &sum_squares);

	// Calculate mean
	ds->mean = sum / ds->count;

	// Calculate standard deviation
	if (ds->count > 1) {
		float variance = (sum_squares - (sum * sum) / ds->count) / ds->count;
		ds->stddev = sqrt(variance);
	} else {
		ds->stddev = 0;
	}
}

void avlds_merge(AVLDS *dest, AVLDS *source) {
	if (dest == NULL || source == NULL || source->root == NULL)
		return;

	// Merge the trees
	avl_merge(&(dest->root), &(source->root));

	// Update the count
	int original_count = dest->count;
	dest->count += source->count;

	// Update statistics using aggregation algorithm
	if (original_count == 0) {
		// If destination was empty, just copy source stats
		dest->mean = source->mean;
		dest->stddev = source->stddev;
	} else if (source->count > 0) {
		// Calculate combined mean and standard deviation
		float combined_mean =
				(original_count * dest->mean + source->count * source->mean) /
				dest->count;

		// For standard deviation, we need the combined variance
		float delta = source->mean - dest->mean;
		float combined_variance =
				((original_count * (dest->stddev * dest->stddev)) +
				 (source->count * (source->stddev * source->stddev)) +
				 ((original_count * source->count * delta * delta) / dest->count)) /
				dest->count;

		dest->mean = combined_mean;
		dest->stddev = sqrt(combined_variance);
	}

	// Clean the source AVLDS after merging
	avlds_clean(source);
}

void avlds_clean(AVLDS *ds) {
	if (ds == NULL)
		return;

	// Clean the AVL tree
	avl_clean(&(ds->root));

	// Reset statistics
	ds->count = 0;
	ds->mean = 0;
	ds->stddev = 0;
}

void add_record(AVLDS *ds, RECORD data) {
	if (ds == NULL)
		return;

	// Check if the record already exists
	AVLNODE *existing = avl_search(ds->root, data.name);
	if (existing) {
		// Update existing record's score
		float old_score = existing->data.score;
		existing->data.score = data.score;

		// Adjust statistics for the score change
		if (ds->count > 0) {
			float diff = data.score - old_score;
			float old_mean = ds->mean;
			ds->mean += diff / ds->count;

			if (ds->count > 1) {
				// Update stddev: requires recalculation
				recalculate_stats(ds);
			}
		}
	} else {
		// Add new record to the AVL tree
		avl_insert(&(ds->root), data);

		// Update statistics
		if (ds->count == 0) {
			// First record
			ds->mean = data.score;
			ds->stddev = 0;
		} else {
			int n = ds->count;
			float old_mean = ds->mean;
			float new_mean = (old_mean * n + data.score) / (n + 1);

			// For standard deviation, using Welford's algorithm
			if (n > 0) {
				float old_variance = ds->stddev * ds->stddev;
				float new_variance =
						old_variance +
						((data.score - old_mean) * (data.score - new_mean) - old_variance) /
								(n + 1);
				ds->stddev = sqrt(new_variance);
			}

			ds->mean = new_mean;
		}

		// Increment count
		ds->count++;
	}
}

void remove_record(AVLDS *ds, char *name) {
	if (ds == NULL || ds->root == NULL || name == NULL)
		return;

	// Find the node to be removed
	AVLNODE *node = avl_search(ds->root, name);
	if (node == NULL)
		return; // Record not found

	float score_to_remove = node->data.score;

	// Remove the node from AVL tree
	avl_delete(&(ds->root), name);

	// Update statistics
	if (ds->count == 1) {
		// Last record being removed
		ds->count = 0;
		ds->mean = 0;
		ds->stddev = 0;
	} else {
		// Update count and recalculate statistics
		ds->count--;

		// For accurate stats after removal, recalculate
		float old_mean = ds->mean;
		float new_mean = (old_mean * (ds->count + 1) - score_to_remove) / ds->count;

		// Need to recalculate standard deviation
		recalculate_stats(ds);
	}
}
