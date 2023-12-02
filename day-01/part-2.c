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

#define NUM_OF_DIGIT_WORDS 9
#define BUFFER_SIZE 50

int charToInt(char c);

char letterBuffer[BUFFER_SIZE];
char letterBufferStr[BUFFER_SIZE + 1];

const char* digitWords[] =
	{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int main() {
	char c;
	char first, second = '\0'; // null char
	int firstDigit, secondDigit;
	int sum = 0;

	FILE *file;
	file = fopen("input-example-part-2.txt", "r");
	if (file == NULL) {
		printf("Could not open file.");
		exit(1);
	}

	while ((c = getc(file)) != EOF) {
		// Alpha character
		if (isalpha(c)) {
			// Add c to buffer, check if any match
		}
		
		// Digit character
		else if (isdigit(c)) {
			if (first == '\0')
				first = c;
			else
				second = c;
		}
		
		// End of line
		else if (c == '\n') {
			firstDigit = charToInt(first);
			secondDigit = (second != '\0')
				? charToInt(second)
				: firstDigit;
			
			int calibrationValue = (firstDigit * 10) + secondDigit;
			printf("Calibration value: %d\n", calibrationValue);
			
			sum = sum + calibrationValue;
			printf("Running total: %d\n\n", sum);
			first = second = '\0';
		}
	}
	
	fclose(file);
	printf("Sum of calibration values: %d\n", sum);	
	return 0;
}

void bufferToString() {
	if (sizeof letterBuffer == 0)
		return;
	
	// int length = sizeof a / sizeof a[0];
	// letterBufferStr[length + 1];

	// Copy buffer to string
	for (int i = 0; i < BUFFER_SIZE; i++) {
		letterBufferStr[i] = letterBuffer[i];
	}
	
	// Add null char to end to terminate string
	letterBufferStr[BUFFER_SIZE] = '\0';
	
	return;
}

int charToInt(char c) {
	if (!isdigit(c))
		return -1; // TODO: handle this in calling code
	
	// Each digit in the range '0'..'9' is guaranteed to be one
	// greater than its previous digit.
	int value = c - '0';
	printf("'%c' -> %d\n", c, value);
	return value;
}

char* findMatch(char c[]) {
	int isMatch = false;
	
	for (int i = 0; i < NUM_OF_DIGIT_WORDS; i++) {
		isMatch = isMatch || strcmp(digitWords[i], c) == 0;
		
		if (isMatch)
			return digitWords[i];
	}
	
	return "";
}
