

#include <math.h>

float norm(float *v, int n) {

	float norm = 0.0f;

	// Sum of the squares
	for (int i = 0; i < n; ++i) {
		norm += *(v + i) * *(v + i);
	}

	// Square root of the sum of of squares

	norm = sqrt(norm);

	return norm;
}
float dot_product(float *v1, float *v2, int n) {

	float dotProduct = 0.0f;

	// Sum of the products of corresponding elements
	for (int i = 0; i < n; ++i) {
		dotProduct += *(v1 + i) * *(v2 + i);
	}

	return dotProduct;
}
void matrix_multiply_vector(float *m, float *v, float *vout, int n) {

	for (int i = 0; i < n; ++i) {
		float sum = 0.0f;
		for (int j = 0; j < n; ++j) {
			// i * n is the row, j is the column
			sum += *(m + i * n + j) * *(v + j);
		}
		*(vout + i) = sum;
	}

	return;
}
void matrix_multiply_matrix(float *m1, float *m2, float *m3, int n) {

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			float sum = 0.0f;
			for (int k = 0; k < n; ++k) {
				// i * n is the row, j is the column
				sum += *(m1 + i * n + k) * *(m2 + k * n + j);
				// k*n is the row, j is the column
			}
			*(m3 + i * n + j) = sum;
		}
	}

	return;
}
