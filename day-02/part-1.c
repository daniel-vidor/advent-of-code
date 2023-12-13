#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Day 2: Cube Conundrum

const char* INPUT_FILE = "input-example-part-1.txt";
const int MAX_LINE_SIZE = 100;
const int MAX_RED_CUBES = 12;
const int MAX_GREEN_CUBES = 13;
const int MAX_BLUE_CUBES = 14;

FILE* open_input_file(const char* filename);
int strsplit(char* string, const char* delim, char** split_string);
char* strsep(char **stringp, const char *delim);
void print_string_array(char** str_arr, int length);

int main() {
    int line_number = 1;
    int token_count;
    char* found;

    char line[MAX_LINE_SIZE];
    char* split_string[100];

    FILE* file = open_input_file(INPUT_FILE);
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("Reading line %d...\n", line_number++);

        line[strcspn(line, "\n")] = '\0'; // Strip off newline
        printf("\t\"%s\"\n", line);

        token_count = strsplit(line, ":", split_string);
        print_string_array(split_string, token_count);

        token_count = strsplit(split_string[1], ";", split_string);
        print_string_array(split_string, token_count);

        char* split_string_sub[100];
        int token_count_sub = 0;
        for (int i = 0; i < token_count; i++) {
            token_count_sub = strsplit(split_string[i], ",", split_string_sub);
            // token_count_sub = strsplit(split_string[i], ",", split_string_sub[token_count_sub]);
        }
        print_string_array(split_string_sub, token_count_sub);

        putchar('\n');
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

/**
 * Splits a given string, `string`, by a given delimiter, `delim`, and outputs the result to `split_string`.
 * Returns the number of split elements.
 */
int strsplit(char* string, const char* delim, char** split_string) {
    printf("Splitting \"%s\" by '%s'...\n", string, delim);

    int count = 0;
    char* token;
    
    while (token = strsep(&string, delim)) {
        printf("\tToken: \"%s\"\n", token);
        split_string[count++] = token;
    }

    return count;
}

/** Prints an array of strings. */
void print_string_array(char** str_arr, int length) {
    printf("Printing string array...\n");
    printf("\t[");

    for (int i = 0; i < length; i++) {
        printf("\"%s\"", str_arr[i]);

        if (i < length - 1)
            printf(", ");
    }

    printf("]\n");
}

/** `strsep` is not in MinGW's environment, so it has been copied here. */
char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}
