#include "mystring.h"

int str_words(char *s) {
	int i;
	int count = 0;
	int in_word = 0;

	// loop until end of string
	for (i = 0; s[i] != '\0'; i++) {
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
			// Current character is a letter, we're in a word
			if (!in_word) {
				// If we weren't in a word, set flag
				in_word = 1;
			}
		} else {
			// Current character is not a letter
			if (in_word) {
				// If we were in a word, increment count
				count++;
				in_word = 0;
			}
		}
	}

	// Count the last word if we ended in one
	if (in_word) {
		count++;
	}

	return count;
}
int str_lower(char *s) {
	int count = 0;
	int i;

	for (i = 0; s[i] != '\0'; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			s[i] = s[i] + ('a' - 'A'); // Convert to lowercase
			count++;
		}
	}

	return count;
}
void str_trim(char *s) {
	int i, j;
	int space_flag = 0;

	// Skip leading spaces
	i = 0;
	while (s[i] == ' ' || s[i] == '\t') {
		i++;
	}

	// If string is all spaces
	if (s[i] == '\0') {
		s[0] = '\0';
		return;
	}

	// Shift characters to remove leading spaces
	if (i > 0) {
		for (j = 0; s[i] != '\0'; j++, i++) {
			s[j] = s[i];
		}
		s[j] = '\0';
	}

	// Handle multiple spaces between words
	i = j = 0;
	while (s[i] != '\0') {
		if (s[i] == ' ' || s[i] == '\t') {
			if (!space_flag) {
				s[j] = ' ';
				j++;
				space_flag = 1;
			}
		} else {
			s[j] = s[i];
			j++;
			space_flag = 0;
		}
		i++;
	}

	// Remove trailing space if exists
	if (j > 0 && s[j - 1] == ' ') {
		j--;
	}

	s[j] = '\0';
}
