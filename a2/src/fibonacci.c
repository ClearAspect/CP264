int iterative_fibonacci(int n) {

	int secondPrev = 0;
	int firstPrev = 1;
	int fibonnacci = 0;

	for (int i = 0; i < n; ++i) {
		secondPrev = firstPrev;
		firstPrev = fibonnacci;
		fibonnacci = secondPrev + firstPrev;
	}

	return fibonnacci;
}

int recursive_fibonacci(int n) {

	if (n <= 1) {
		return n;
	} else {
		return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
	}

	return 0;
}

int dpbu_fibonacci(int *f, int n) {
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;

	// Initialize base cases
	f[0] = 0;
	f[1] = 1;

	// Build up the array from bottom to top
	for (int i = 2; i <= n; i++) {
		f[i] = f[i - 1] + f[i - 2];
	}

	return f[n];
}

int dptd_fibonacci(int *f, int n) {
	// Base cases
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;

	// If value is already computed, return it
	if (f[n] != -1) {
		return f[n];
	}

	// Compute and store the value
	f[n] = dptd_fibonacci(f, n - 1) + dptd_fibonacci(f, n - 2);
	return f[n];
}
