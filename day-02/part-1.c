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
char* strsep(char **stringp, const char *delim);
void print_string_array(char** str_arr);
char** split(char* string, const char* delim);

int main() {
    char c;
    char* found;
    FILE* file;
    file = open_input_file(INPUT_FILE);

    char line[MAX_LINE_SIZE];
    char** str_arr_colon;
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        str_arr_colon = split(line, ":");
        print_string_array(str_arr_colon);
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

char** split(char* string, const char* delim) {
    string[strcspn(string, "\n")] = '\0'; // Strip off newline
    printf("Splitting \"%s\" by '%s'\n", string, delim);

    char* split_string[50];
    int count = 0;
    char* copied_string;
    strcpy(copied_string, string);
    char* token;
    
    while (token = strsep(&copied_string, delim)) {
        printf(token);
        // split_string[count++] = token;
        strcpy(split_string[count++], token);
    }

    return &split_string;
}

void print_string_array(char** str_arr) {
    printf("Printing string array...\n");
    int length = (sizeof str_arr) / (sizeof str_arr[0]);
    for (int i = 0; i < length; i++)
        printf("[%s], ", str_arr[i]);

    putchar('\n');
}

/** strsep is not in MinGW's environment, so it has been copied here. */
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
