/*
    Read lines from a file given as a command line argument and print out the 
    valid positive numbers found on the lines. A valid number is defined as 
    a number separated by spaces (exception start and end of a line where 
    the number is not separated by space).

    Presume that a line is at most 100 chars.

    Example:
        Input:
        123 ui12 8998aaa 21
        9abe 87 iii123 55 109

        Output:
        123 21 87 55 109
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void process_line(char *line) {
    char *space_after = line;

    // Is first char a digit ?
    if(isdigit(*line)) {
        // There might be a valid number at the start of the line
        // Transform the string to number
        long number = strtol(line, &space_after, 10);

        if(*space_after == ' ' || *space_after == '\n') {
            // Is valid number
            printf("Extracted number: %ld\n", number);
        }
    }

    // Go to next digit
    char *ptr = space_after + strcspn(space_after, "0123456789");
    while(*ptr != '\0') { 
        long number = strtol(ptr, &space_after, 10);

        // is separated by ' ' and ' ' or ' ' and '\n'
        if(*(ptr - 1) == ' ' && (*space_after == ' ' || *space_after == '\n')) {
            // Valid number
            printf("Extracted number: %ld\n", number);
        } 

        // Go to next digit
        ptr = space_after + strcspn(space_after, "0123456789");
    }
}

void process_file(FILE *input_file) {
    char line[100];

    while(fgets(line, 100, input_file)) {
        process_line(line);
    }
}

int main(int argc, char *argv[]) {
    // Verify there are enough arguments
    if(argc != 2) {
        printf("Usage ./p <file_name>\n");
        exit(1);
    }

    // Open file
    FILE *input_file = fopen(argv[1], "r");
    if(input_file == NULL) {
        printf("Error while opening file\n");
        exit(1);
    }

    process_file(input_file);

    // Close file
    if(fclose(input_file) != 0) {
        printf("Error while closing file\n");
        exit(1);
    }

    return 0;
}