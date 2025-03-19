
#include "myrecord_bst.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void add_record(BSTDS *ds, RECORD record) {
	// Check if the record already exists
	BSTNODE *existing_node = bst_search(ds->root, record.name);

	if (existing_node != NULL) {
		// Update existing record - need to adjust statistics
		float old_score = existing_node->data.score;
		float old_mean = ds->mean;

		// Update the node with new data
		existing_node->data = record;

		// Recalculate statistics (mean and variance)
		if (ds->count > 0) {
			// Update mean
			ds->mean = old_mean + (record.score - old_score) / ds->count;

			// Update standard deviation using the updated variance
			// We need to adjust the sum of squared differences
			float old_variance = ds->stddev * ds->stddev;
			float new_variance =
					old_variance + ((record.score - old_score) *
													(record.score - ds->mean + old_score - old_mean)) /
														 ds->count;
			ds->stddev = sqrt(new_variance);
		}
	} else {
		// Insert new record
		bst_insert(&(ds->root), record);

		// Update statistics using online algorithm
		ds->count++;

		if (ds->count == 1) {
			// First record
			ds->mean = record.score;
			ds->stddev = 0.0;
		} else {
			// Welford's online algorithm for mean and variance
			float old_mean = ds->mean;
			float delta = record.score - old_mean;

			// Update mean
			ds->mean = old_mean + delta / ds->count;

			// Update variance (for standard deviation)
			float delta2 = record.score - ds->mean;
			float old_variance = ds->stddev * ds->stddev;
			float m2 = old_variance * (ds->count - 1) + delta * delta2;
			ds->stddev = sqrt(m2 / ds->count);
		}
	}
}

void remove_record(BSTDS *ds, char *name) {
	// Find the node to be deleted
	BSTNODE *node_to_delete = bst_search(ds->root, name);

	if (node_to_delete != NULL) {
		float score_to_remove = node_to_delete->data.score;

		// Delete the node from the BST
		bst_delete(&(ds->root), name);

		// Update statistics
		ds->count--;

		if (ds->count == 0) {
			// Tree is empty now
			ds->mean = 0.0;
			ds->stddev = 0.0;
		} else {
			// Update mean
			float old_mean = ds->mean;
			float new_mean =
					(old_mean * (ds->count + 1) - score_to_remove) / ds->count;

			// Update standard deviation
			float old_variance = ds->stddev * ds->stddev;
			float old_sum_squared = old_variance * (ds->count + 1) +
															(ds->count + 1) * old_mean * old_mean;
			float new_sum = (ds->count + 1) * old_mean - score_to_remove;
			float new_sum_squared =
					old_sum_squared - score_to_remove * score_to_remove;
			float new_variance = new_sum_squared / ds->count -
													 (new_sum / ds->count) * (new_sum / ds->count);

			ds->mean = new_mean;
			ds->stddev = sqrt(new_variance);
		}
	}
}

void bstds_clean(BSTDS *ds) {
	// Clean the BST
	bst_clean(&(ds->root));

	// Reset statistics
	ds->count = 0;
	ds->mean = 0.0;
	ds->stddev = 0.0;
}
