int power_overflow(int b, int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 0;
	if (b == 0)
		return 0;
	if (b == 1)
		return 0;
	if (b == -1) {
		if (n % 2 == 0)
			return 0;
		else
			return 1;
	}

	int result = 1;

	// Check for overflow before each multiplication
	for (int i = 0; i < n; i++) {
		// Check if multiplication will exceed INT_MAX
		if (b > 0 && result > (2147483647 / b)) {
			return 1; // Overflow
		}
		// Check if multiplication will exceed INT_MIN
		if (b < 0 && result < (-2147483648 / b)) {
			return 1; // Overflow
		}

		result *= b;
	}

	return 0;
}

int mypower(int b, int n) {
	if (power_overflow(b, n))
		return 0;

	int product = 1;
	for (int i = 0; i < n; ++i) {
		product = product * b;
	}

	return product;
}

int powersum(int b, int n) {
	// Handle invalid input
	if (n < 0)
		return 0;
	if (n == 0)
		return 0;

	int sum = 1;
	int prev_sum;
	int current_power;

	// Calculate sum of powers from b^1 to b^n
	for (int i = 1; i <= n; i++) {
		// Calculate current power using mypower
		current_power = mypower(b, i);

		// If mypower returned 0, there was an overflow
		if (current_power == 0 && b != 0) {
			return 0;
		}

		// Save previous sum to check for overflow
		prev_sum = sum;
		sum += current_power;

		// Check for overflow in addition
		if (current_power > 0 && sum < prev_sum) {
			return 0; // positive overflow
		}
		if (current_power < 0 && sum > prev_sum) {
			return 0; // negative overflow
		}
	}

	return sum;
}
