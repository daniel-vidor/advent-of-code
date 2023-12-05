#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Day 2: Cube Conundrum

const char* INPUT_FILE = "input-example-part-1.txt";
const int MAX_LINE_SIZE = 50;
const int MAX_RED_CUBES = 12;
const int MAX_GREEN_CUBES = 13;
const int MAX_BLUE_CUBES = 14;

FILE* open_input_file(const char* filename);

int main() {
    char c;
    char* found;
    FILE* file;
    file = open_input_file(INPUT_FILE);

    char* line[MAX_LINE_SIZE];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    return 0;
}

FILE* open_input_file(const char* filename) {
    FILE *file;
    file = fopen(filename, "r");
    
	if (file == NULL) {
		printf("Could not open file.");
		exit(1);
	}

    return file;
}

char** split(char* string, char* delim) {
    char** s;

    int i = strcspn(string, delim);

    return s;
}
