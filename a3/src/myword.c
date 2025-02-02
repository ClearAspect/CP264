#include "myword.h"

int create_dictionary(FILE *fp, char *dictionary) {
	// Buffer to hold each line from the file
	char buffer[1024];
	// Counter for total words added to dictionary
	int word_count = 0;
	// Current position in dictionary array
	int dict_pos = 0;

	// Read file line by line
	while (fgets(buffer, sizeof(buffer), fp)) {
		// Remove leading/trailing whitespace
		str_trim(buffer);
		// Pointer to current character in buffer
		char *current = buffer;
		// Temporary array to build each word
		char word[20];
		// Current position in word array
		int word_pos = 0;

		// Process each character in the line
		while (*current) {
			// Check if character is a letter
			if ((*current >= 'A' && *current <= 'Z') ||
				(*current >= 'a' && *current <= 'z')) {
				// Add letter to word if space available
				if (word_pos < 19) {
					word[word_pos++] = *current;
				}
			} else if (word_pos > 0) {
				// Non-letter found and word exists, process the word
				word[word_pos] = '\0';
				// Convert word to lowercase
				str_lower(word);

				// Copy word to dictionary array
				strcpy(dictionary + dict_pos, word);
				dict_pos += strlen(word) + 1; // +1 for null terminator
				word_count++;
				word_pos = 0;
			}
			current++;
		}

		// Handle last word in line if exists
		if (word_pos > 0) {
			word[word_pos] = '\0';
			str_lower(word);
			// Add final word to dictionary
			strcpy(dictionary + dict_pos, word);
			dict_pos += strlen(word) + 1;
			word_count++;
		}
	}

	// Add final null terminator to mark end of dictionary
	dictionary[dict_pos] = '\0';
	return word_count;
}

BOOLEAN contain_word(char *dictionary, char *word) {
	// Create a temporary buffer for the search word
	char temp_word[20];
	// Copy the word to temp buffer (max 19 chars)
	strncpy(temp_word, word, 19);
	// Ensure null termination
	temp_word[19] = '\0';
	// Convert to lowercase for case-insensitive comparison
	str_lower(temp_word);

	// Buffer to store each word from dictionary
	char dict_word[20];
	// Current position in dictionary array
	int pos = 0;

	// Iterate through dictionary until end
	while (dictionary[pos] != '\0') {
		int i = 0;
		// Extract next word from dictionary
		while (dictionary[pos] != '\0' && i < 19) {
			dict_word[i++] = dictionary[pos++];
		}
		// Ensure null termination of dictionary word
		dict_word[i] = '\0';
		pos++; // Skip null terminator between words

		// Compare current dictionary word with search word
		if (strcmp(dict_word, temp_word) == 0) {
			return TRUE;
		}
	}

	// Word not found in dictionary
	return FALSE;
}

WORDSTATS process_words(FILE *fp, WORD *words, char *dictionary) {
	// Initialize statistics and tracking variables
	WORDSTATS stats = {0, 0, 0}; // Initialize all counts to 0
	char buffer[1024];
	int unique_count = 0;

	// Process file line by line
	while (fgets(buffer, sizeof(buffer), fp)) {
		stats.line_count++;
		str_trim(buffer);
		stats.word_count += str_words(buffer);

		char *current = buffer;
		char word[20];
		int word_pos = 0;

		// Extract words character by character from the line
		while (*current) {
			// Add letters to current word
			if ((*current >= 'A' && *current <= 'Z') ||
				(*current >= 'a' && *current <= 'z')) {
				if (word_pos < 19) {
					word[word_pos++] = *current;
				}
			} else if (word_pos > 0) {
				// Process completed word
				word[word_pos] = '\0';

				// If word is not in dictionary, process it
				if (!contain_word(dictionary, word)) {
					BOOLEAN found = FALSE;
					char temp_word[20];
					strncpy(temp_word, word, 19);
					temp_word[19] = '\0';
					str_lower(temp_word);

					// Check if word already exists in our tracking array
					for (int i = 0; i < unique_count; i++) {
						char existing[20];
						strncpy(existing, words[i].word, 19);
						existing[19] = '\0';
						str_lower(existing);

						if (strcmp(existing, temp_word) == 0) {
							words[i].count++;
							found = TRUE;
							break;
						}
					}

					// Add new unique word to tracking array
					if (!found) {
						strncpy(words[unique_count].word, word, 19);
						words[unique_count].word[19] = '\0';
						words[unique_count].count = 1;
						unique_count++;
						stats.keyword_count++;
					}
				}
				word_pos = 0;
			}
			current++;
		}

		// Handle last word in the line if it exists
		if (word_pos > 0) {
			word[word_pos] = '\0';

			if (!contain_word(dictionary, word)) {
				BOOLEAN found = FALSE;
				char temp_word[20];
				strncpy(temp_word, word, 19);
				temp_word[19] = '\0';
				str_lower(temp_word);

				// Check if last word already exists in tracking array
				for (int i = 0; i < unique_count; i++) {
					char existing[20];
					strncpy(existing, words[i].word, 19);
					existing[19] = '\0';
					str_lower(existing);

					if (strcmp(existing, temp_word) == 0) {
						words[i].count++;
						found = TRUE;
						break;
					}
				}

				// Add last word if it's unique
				if (!found) {
					strncpy(words[unique_count].word, word, 19);
					words[unique_count].word[19] = '\0';
					words[unique_count].count = 1;
					unique_count++;
					stats.keyword_count++;
				}
			}
		}
	}

	return stats;
}
