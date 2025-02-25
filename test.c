

int horner(int p[], int n, int x) {

	int result = p[0];

	for (int i = 1; i < n; ++i) {
		result = result * x + p[i];
	}
	return result;
}

void reverse(char *s) {

	if (s == 0)
		return;

	int len = 0;
	while (s[len] != 0)
		++len;

	for (int i = 0; i < len / 2; ++i) {
		char temp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = temp;
	}
}

int str2int(char *s) {

	int result = 0;
	int sign = 1;
	int i = 0;

	if (s[0] == '-') {
		sign = -1;
		i = 1;
	}

	while (s[i] != '\0') {
		if (s[i] >= '0' && s[i] <= '9') {
			result = result * 10 + (s[i] - '0');
		}
		++i;
	}

	return result * sign;
}

void int2str(int a, char s[]) {
	char temp[12]; // Enough for 32-bit int including sign and null
	int i = 0;
	int j = 0;

	// Handle 0 specially
	if (a == 0) {
		s[0] = '0';
		s[1] = '\0';
		return;
	}

	// Handle negative numbers
	if (a < 0) {
		s[j++] = '-';
		a = -a;
	}

	// Convert to digits and store temporarily
	while (a > 0) {
		temp[i++] = (a % 10) + '0';
		a = a / 10;
	}

	// Copy digits in reverse order to get correct orientation
	while (i > 0) {
		s[j++] = temp[--i];
	}

	s[j] = '\0'; // Null terminate
}
