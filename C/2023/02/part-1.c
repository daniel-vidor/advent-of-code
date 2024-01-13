#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Day 2: Cube Conundrum

// Example line of input:
// "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"

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
    int game_id = 1;
    int sum_of_possible_game_ids = 0;
	bool game_is_possible = true;
    char line[MAX_LINE_SIZE];
    char* line_substrings[10];
    char* sets[100];
    char* cubes[100];
    char* cube_phrase[100];

    FILE* file = open_input_file(INPUT_FILE);
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("Reading line %d...\n", game_id);

        line[strcspn(line, "\n")] = '\0'; // Strip off newline
        printf("\t\"%s\"\n", line);

        // line = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
        int token_count = strsplit(line, ":", line_substrings);
        print_string_array(line_substrings, token_count);

        // game = "3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"
        char* game_number_phrase = line_substrings[0];
        char* game = line_substrings[1];
        int set_count = strsplit(game, ";", sets);
        print_string_array(sets, set_count);

        // sets = ["3 blue, 4 red", "1 red, 2 green, 6 blue", "2 green"]
        for (int i = 0; i < set_count; i++) {
            int cube_count = strsplit(sets[i], ",", cubes);
            print_string_array(cubes, cube_count);

            // cubes = ["3 blue", "4 red"]
            for (int i = 0; i < cube_count; i++) {
                _ = strsplit(cubes[i], " ", cube_phrase)

				// cube_phrase = ["3", "blue"]
				string numberString = cube_phrase[0];
				int number_of_cubes = atoi(numberString);
				string colour = cube_phrase[1];
				
				if (colour == "red" && number_of_cubes > MAX_RED_CUBES
					|| colour = "green" && number_of_cubes > MAX_GREEN_CUBES
					|| colour = "blue" && number_of_cubes > MAX_BLUE_CUBES) {
					game_is_possible = false;
				}
            }
        }

        if (game_is_possible) {
            printf("%s is possible", game_number_phrase);
            sum_of_possible_game_ids += game_id;
        }

        putchar('\n');
        game_id++;
    }

    return 0;
}

FILE* open_input_file(const char* filename) {
    FILE *file;
    file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Could not open file '%s'", filename);
        exit(1);
    }

    return file;
}

/**
 * @ Splits a given string, `string`, by a given delimiter, `delim`, and outputs the result to `split_string`.
 * @returns the number of split elements.
 */
int strsplit(char* string, const char* delim, char** split_string) {
    printf("Splitting \"%s\" by '%s'...\n", string, delim);

    int count = 0;
    char *token, *result;
    
    while (token = strsep(&string, delim)) {
        printf("\tToken: \"%s\"\n", token);

        // Shift pointer from 0th character to 1st character; effectively removing the first character from the string.
        if (token[0] == ' ') {
            // printf("Space! %c %c\n", token[0], token[1]);
            // token = token + 1;
            if (strlen(token) > 1) {
                printf("A ");
                result = &token[1];
            }
            else {
                printf("B ");
                result = token;
            }
        }

        split_string[count++] = result;
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
