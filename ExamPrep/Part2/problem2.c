/*
    You have a file containing text lines, each line possibly 
    containing a specific pattern with square brackets denoting a range. 
    Maximum 500 characters on a line.

    The pattern follows the format: <word>[<start>-<end>] 
    - word is a string
    - start and end are unsigned numbers

    A cat[1-3] here. -> A cat1, cat2, cat3 here.

    struct prefix word start end and postfix
    Read lines using fgets and break it down into the struct above
    idx = start, end
        Print prefix + word + idx + postix

    A cat[1-3] here.

    // Process line
    we use strchr to find '['
    if doesn't exist print unformatted string  
    copy in prefix_aux from start to '[' address
    sscanf(address_bracket, "[%u-%u], &start, &end")
    we use strchr to find ']'
    copy into postfix from address_closed_bracket until the end of the line

    // Breaking prefix_aux into prefix and word 
    // by going backwards from address_bracket till 
    // we find space or we reach start of the string

    // Print line
    idx = start, end
        Print prefix + word + idx + postix
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define FILE_PATH "test-problem-2"
#define MAX_CHARS_PER_LINE 500

typedef struct {
    char prefix[MAX_CHARS_PER_LINE];
    char word[MAX_CHARS_PER_LINE];
    unsigned start, end;
    char postfix[MAX_CHARS_PER_LINE];
    bool needs_formatting;
}LINE;

LINE process_line(char *line_string) {
    LINE line;
    // we use strchr to find '['
    char *open_bracket = strchr(line_string, '[');

    // if doesn't exist print unformatted string  
    if(open_bracket == NULL) {
        strcpy(line.prefix, line_string);
        line.needs_formatting = false;
        return line;
    }
    line.needs_formatting = true;

    // copy in prefix_aux from start to '[' address
    char prefix_aux[MAX_CHARS_PER_LINE];
    int no_characters = open_bracket - line_string;
    strncpy(prefix_aux, line_string, no_characters);
    prefix_aux[no_characters] = '\0';

    // # Breaking prefix_aux into prefix and word 
    // # by going backwards from address_bracket till 
    // # we find space or we reach start of the string

    // Find last space or start of string
    char *end_of_prefix = prefix_aux + strlen(prefix_aux);
    // Initially at end of prefix_aux
    char *start_of_word = prefix_aux + strlen(prefix_aux);

    while(start_of_word != line_string) {
        if(*start_of_word == ' ') {
            // Jump over ' '
            ++start_of_word;
            break;
        }
        --start_of_word;
    }

    // Separate word from prefix
    no_characters =  end_of_prefix - start_of_word;
    strncpy(line.word, start_of_word, no_characters);
    line.word[no_characters] = '\0';

    // Put prefix into line
    no_characters = start_of_word - prefix_aux;
    strncpy(line.prefix, prefix_aux, no_characters);
    line.prefix[no_characters] = '\0';

    // sscanf(address_bracket, "[%u-%u], &start, &end")
    sscanf(open_bracket, "[%u-%u]", &line.start, &line.end);

    // we use strchr to find ']'
    char *closed_bracket = strchr(line_string, ']');

    // copy into postfix from address_closed_bracket until the end of the line
    // closed_bracket + 1 to jump over ']'
    closed_bracket = closed_bracket + 1;

    char *end_of_line = line_string + strlen(line_string); 
    no_characters = end_of_line - closed_bracket;
    strncpy(line.postfix, closed_bracket, no_characters);
    line.postfix[no_characters] = '\0';

    return line;
}

void print_formatted_line(LINE line) {
    if(!line.needs_formatting) {
        printf("%s\n", line.prefix);
        return;
    }

    printf("%s", line.prefix);
    for(unsigned idx = line.start; idx < line.end; ++idx) {
        printf("%s%d, ", line.word, idx);
    }
    printf("%s%d", line.word, line.end);
    printf("%s\n", line.postfix);
}

void print_formatted_lines(FILE *input) {
    char line_string[MAX_CHARS_PER_LINE];
    while(fgets(line_string, MAX_CHARS_PER_LINE, input)) {
        LINE line = process_line(line_string);
        print_formatted_line(line);
    }
}


int main() {
    FILE *f = fopen(FILE_PATH, "r");
    if(f == NULL) {
        perror("Error with opening file");
        exit(-1);
    }

    print_formatted_lines(f);

    if(fclose(f) != 0) {
        perror("Error with closing file");
        exit(-1);
    }
    return 0;
}