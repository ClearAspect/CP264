#include <math.h>

int solution_type(float a, float b, float c) {
	// Check if equation is not quadratic (a=0)
	if (a == 0) {
		return 0;
	}

	float discriminant = b * b - 4 * a * c;

	// If discriminant > 0, equation has two distinct real roots
	if (discriminant > 0) {
		return 2;
	}
	// If discriminant = 0, equation has one repeated real root
	else if (discriminant == 0) {
		return 1;
	}
	// If discriminant < 0, equation has two complex roots
	else {
		return 3;
	}
}

float real_root_big(float a, float b, float c) {
	int type = solution_type(a, b, c);

	// Return 0 if not a quadratic equation or has complex roots
	if (type == 0 || type == 3) {
		return 0;
	}

	float discriminant = b * b - 4 * a * c;

	// For both one real root or two real roots, calculate the bigger one
	// Using -b + sqrt(discriminant)/(2a) for the bigger root
	return (-b + sqrt(discriminant)) / (2 * a);
}

float real_root_small(float a, float b, float c) {
	int type = solution_type(a, b, c);

	// Return 0 if not a quadratic equation or has complex roots
	if (type == 0 || type == 3) {
		return 0;
	}

	float discriminant = b * b - 4 * a * c;

	// For both one real root or two real roots, calculate the smaller one
	// Using -b - sqrt(discriminant)/(2a) for the smaller root
	return (-b - sqrt(discriminant)) / (2 * a);
}
