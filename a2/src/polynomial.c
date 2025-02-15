#include "polynomial.h"

float horner(float *p, int n, float x) {

	// Start with the last coefficient (largest power)
	float result = *p;

	for (int i = 1; i < n; ++i) { // Start with the next highest power
		result = result * x + p[i];
		// result = result * x + *(p + i);
	}

	return result;
}

void derivative(float *p, float *d, int n) {

	for (int i = 0; i < n - 1; ++i) {
		*(d + i) = *(p + i) * (n - 1 - i);
	}

	return;
}

float newton(float *p, int n, float x0) {
	// Constants
	const float EPSILON = 1e-6;
	const int MAX_ITER = 100;

	float x = x0;	// Initial guess
	float d[n - 1]; // Create empty array for derivative coefficients
	float fx, fpx;	// f(x) and f'(x)
	int iter = 0;	// iteration count

	// Get derivative coefficients
	derivative(p, d, n);

	// Newton's method
	while (iter < MAX_ITER) {

		// Calculate f(x) and f'(x)
		fx = horner(p, n, x);
		fpx = horner(d, n - 1, x);

		if (fpx == 0) { // if f'(x) is zero
			return x;
		}

		float x_new = x - (fx / fpx); // Update x

		// Check if x is close enough to the root
		float x_diff = x_new - x;
		if (x_diff < 0) { // abs
			x_diff = -x_diff;
		}
		if (x_diff < EPSILON) { // if x is close enough to the root
			return x_new;
		}

		x = x_new;
		iter++;
	}

	return x;
}
