#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

// Day 1: Trebuchet?! (Part 1)
//
// On each line, the calibration value can be found by combining the first
// digit and the last digit (in that order) to form a single two-digit number.
// What is the sum of all of the calibration values?

int charToInt(char c);

int main() {
	char c;
	char first, second = '\0'; // null char
	int firstDigit, secondDigit;
	int sum = 0;

	FILE *file;
	file = fopen("input-example-part-1.txt", "r");
	if (file == NULL) {
		printf("Could not open file.");
		exit(1);
	}

	while ((c = getc(file)) != EOF) {
		// Digit character
		if (isdigit(c)) {
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

int charToInt(char c) {
	// Each digit in the range '0'..'9' is guaranteed to be one
	// greater than its previous digit.
	int value = c - '0';
	printf("'%c' -> %d\n", c, value);
	return value;
}
