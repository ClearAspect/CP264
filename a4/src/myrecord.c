
#include "myrecord.h"
#include <stdlib.h>

GRADE grade(float score) {

	GRADE result = {"F"};

	if (score >= 90 && score <= 100) {
		result = (GRADE){"A+"};
	} else if (score >= 85) {
		result = (GRADE){"A"};
	} else if (score >= 80) {
		result = (GRADE){"A-"};
	} else if (score >= 77) {
		result = (GRADE){"B+"};
	} else if (score >= 73) {
		result = (GRADE){"B"};
	} else if (score >= 70) {
		result = (GRADE){"B-"};
	} else if (score >= 67) {
		result = (GRADE){"C+"};
	} else if (score >= 63) {
		result = (GRADE){"C"};
	} else if (score >= 60) {
		result = (GRADE){"C-"};
	} else if (score >= 57) {
		result = (GRADE){"D+"};
	} else if (score >= 53) {
		result = (GRADE){"D"};
	} else if (score >= 50) {
		result = (GRADE){"D-"};
	} else {
		result = (GRADE){"F"};
	}

	return result;
}

int import_data(FILE *fp, RECORD *dataset) {
	int count = 0;
	char line[1024]; // Buffer for reading lines

	// Check if file pointer is valid
	if (fp == NULL || dataset == NULL) {
		return 0;
	}

	// Read file line by line
	while (fgets(line, sizeof(line), fp) != NULL) {
		// Parse name and score from each line
		if (sscanf(line, "%[^,], %f", dataset[count].name,
				   &dataset[count].score) == 2) {
			count++;
		}
	}

	return count;
}

STATS process_data(RECORD *dataset, int count) {
	STATS result = {0, 0.0, 0.0, 0.0};
	float sum = 0.0, sum_squared = 0.0;
	float *scores;

	if (dataset == NULL || count < 1) {
		return result;
	}

	// Allocate temporary array for sorting (median calculation)
	scores = (float *)malloc(count * sizeof(float));
	if (scores == NULL)
		return result;

	// Calculate mean and copy scores
	for (int i = 0; i < count; i++) {
		sum += dataset[i].score;
		scores[i] = dataset[i].score;
	}
	result.count = count;
	result.mean = sum / count;

	// Calculate standard deviation
	// Summation of (x - mean)^2
	for (int i = 0; i < count; i++) {
		float diff = dataset[i].score - result.mean;
		sum_squared += diff * diff;
	}
	// Standard deviation = sqrt(sum / count)
	result.stddev = sqrt(sum_squared / count);

	// Calculate median (sort scores first)
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (scores[j] > scores[j + 1]) {

				float temp = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = temp;
			}
		}
	}

	if (count % 2 == 0) {
		// Even number of scores (average of two middle elements)
		result.median = (scores[count / 2 - 1] + scores[count / 2]) / 2.0;
	} else {
		// Odd number of scores (middle element)
		result.median = scores[count / 2];
	}

	free(scores);
	return result;
}

int report_data(FILE *fp, RECORD *dataset, STATS stats) {
	if (fp == NULL || dataset == NULL || stats.count < 1) {
		return 0;
	}

	// Create a copy of dataset for sorting
	RECORD *sorted = (RECORD *)malloc(stats.count * sizeof(RECORD));
	if (sorted == NULL)
		return 0;

	// Copy data
	for (int i = 0; i < stats.count; i++) {
		sorted[i] = dataset[i];
	}

	// Sort by score in descending order
	for (int i = 0; i < stats.count - 1; i++) {
		for (int j = 0; j < stats.count - i - 1; j++) {
			if (sorted[j].score < sorted[j + 1].score) {
				RECORD temp = sorted[j];
				sorted[j] = sorted[j + 1];
				sorted[j + 1] = temp;
			}
		}
	}

	// Print statistics
	fprintf(fp, "stats:value\n");
	fprintf(fp, "count:%d\n", stats.count);
	fprintf(fp, "mean:%.2f\n", stats.mean);
	fprintf(fp, "stdev:%.2f\n", stats.stddev);
	fprintf(fp, "median:%.2f\n\n", stats.median);

	// Print sorted records with grades
	fprintf(fp, "name:score,grade\n");

	for (int i = 0; i < stats.count; i++) {
		GRADE g = grade(sorted[i].score);
		fprintf(fp, "%s:%.1f:%s\n", sorted[i].name, sorted[i].score,
				g.letter_grade);
	}

	free(sorted);
	return 1;
}
