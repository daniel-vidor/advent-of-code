#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Day 1: Trebuchet?! (Part 2)
//
// It looks like some of the digits are actually spelled out with letters: one,
// two, three, four, five, six, seven, eight, and nine also count as valid
// "digits".

#define NUM_OF_DIGIT_WORDS 10
#define BUFFER_SIZE 100

int char_to_int(char c);
void store_digit(int d, int *first, int *second);
void push_into_letter_buffer(char c);
void buffer_to_string();
int find_match(char c[], int length);
void clear_letter_buffer();

char letterBuffer[BUFFER_SIZE];
char letterBufferStr[BUFFER_SIZE + 1];
int letterBufferLength = 0;

const char* digitWords[] =
	{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int main() {
	char c;
	// char first, second;
	int firstDigit, secondDigit;
	int sum = 0;

	// first = second = '\0'; // null char
	firstDigit = secondDigit = -1;

	FILE *file;
	file = fopen("input.txt", "r");
	// file = fopen("input-example-part-2.txt", "r");
	if (file == NULL) {
		printf("Could not open file.");
		exit(1);
	}

	while ((c = getc(file)) != EOF) {
		// printf("'%c'\n", c);
		if (c != '\n')
			putchar(c);

		// Digit character
		if (isdigit(c)) {
			clear_letter_buffer();
			int result = char_to_int(c);
			if (result != -1)
				store_digit(result, &firstDigit, &secondDigit);
		}

		// Alpha character
		else if (isalpha(c)) {
			push_into_letter_buffer(c);
			buffer_to_string();
			// letterBufferStr = buffer_to_string(letterBuffer);
			int result = find_match(letterBufferStr, letterBufferLength);
			if (result != -1) {
				store_digit(result, &firstDigit, &secondDigit);
				clear_letter_buffer();
			}
		}

		// End of line
		else if (c == '\n') {

			// Handle if there are no digits
			if (firstDigit == -1 && secondDigit == -1)	
				firstDigit = secondDigit = 0;

			// Handle when there is only one digit
			else if (firstDigit != -1 && secondDigit == -1) {
				secondDigit = firstDigit;
				// firstDigit = 0;
			}

			int calibrationValue = (firstDigit * 10) + secondDigit;
			// printf("Calibration value: %d\n\n", calibrationValue);
			printf(": %d\n", calibrationValue);

			sum = sum + calibrationValue;
			// printf("Running total: %d\n\n", sum);
			
			// Clear state
			firstDigit = secondDigit = -1;
			clear_letter_buffer();
		}
	}
	
	fclose(file);
	printf("Sum of calibration values: %d\n", sum);	
	return 0;
}

void store_digit(int d, int *first, int *second) {
	if (*first == -1)
		*first = d;
	else
		*second = d;
}

/** Adds a character to the letter buffer. */
void push_into_letter_buffer(char c) {
	letterBuffer[letterBufferLength++] = c;
}

void clear_letter_buffer() {
	memset(letterBuffer, 0, sizeof letterBuffer);
	memset(letterBufferStr, 0, sizeof letterBufferStr);
	letterBufferLength = 0;
}

void buffer_to_string() {
	// if (sizeof letterBuffer == 0)
	// 	letterBufferStr = "";
	
	// Copy buffer to string
	for (int i = 0; i < BUFFER_SIZE; i++) {
		letterBufferStr[i] = letterBuffer[i];
	}
	
	// Add null char to end to terminate string
	letterBufferStr[BUFFER_SIZE] = '\0';
	
	return;
}

/** Converts a digit character to its int equivalent, e.g. '3' -> 3. */
int char_to_int(char c) {
	if (!isdigit(c))
		return -1; // TODO: handle this in calling code
	
	// Each digit in the range '0'..'9' is guaranteed to be one
	// greater than its previous digit.
	int value = c - '0';
	// printf("'%c' -> %d\n", c, value);

	return value;
}

/** Tries to match a string to a digit word. */
// TODO: check each substring starting from right, not just the entire buffer.
// i.e. handle an input buffer like "wothree".
int find_match(char str[], int len) {
	// printf("find_match: %s\n", str);

	for (int i = 0; i < len; i++) {
		char *substr = &str[len - i - 1];
		// printf("substr: %s\n", substr);

		for (int j = 0; j < NUM_OF_DIGIT_WORDS; j++) {
			if (strcmp(digitWords[j], substr) == 0) {
				// printf("\"%s\" -> \"%s\" -> %d\n", str, substr, j);
				return j;
			}
		}
	}
	return -1;
}
