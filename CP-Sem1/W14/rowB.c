/*
    Row B. Sorting text. Design a data structure that stores a line of text, 
    together with its length (in characters) and number of words. Read all 
    lines of a file named on the command line into an array of such structures. 

    Sort and print the file with lines in increasing order of length, breaking 
    ties first in decreasing order of words and then in alphabetical order. 
    You may consider at most 200 lines of maximum 200 characters each.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXIMUM_LINES 200
#define MAXIMUM_CHARS_PER_LINE 200

void throw_error(const char *msg) {
    perror(msg);
    exit(1);
}

FILE *open_file(const char *path) {
    FILE *f = fopen(path, "r");
    if(f == NULL) {
        throw_error("Error with file opening");
    }
    return f;
}

void close_file(FILE *f) {
    if(fclose(f) != 0) {
        throw_error("Error with closing file");
    }
}

/*
    Plan:
        1. Process a line into a struct line
        2. Process all lines into a struct text
        3. Sort lines based on criteria
*/

// 1. Process a line into a struct line

typedef struct line {
    char text[MAXIMUM_CHARS_PER_LINE];
    unsigned size, number_of_words;
}LINE;

// See the visualitation of the function here: (Copy full link) https://pythontutor.com/render.html#code=%23include%20%3Cstring.h%3E%0Aunsigned%20get_number_of_words%28const%20char%20*input_line%29%20%7B%0A%20%20%20%20const%20char%20*pointer%20%3D%20strchr%28input_line,%20'%20'%29%3B%0A%20%20%20%20unsigned%20number_of_words%20%3D%200%3B%0A%0A%20%20%20%20while%28pointer%29%20%7B%0A%20%20%20%20%20%20%20%20%2B%2Bnumber_of_words%3B%0A%0A%20%20%20%20%20%20%20%20//%20Jump%20over%20'%20'%20and%20go%20to%20next%20'%20'%0A%20%20%20%20%20%20%20%20%2B%2Bpointer%3B%0A%20%20%20%20%20%20%20%20pointer%20%3D%20strchr%28pointer,%20'%20'%29%3B%0A%20%20%20%20%7D%0A%0A%20%20%20%20return%20number_of_words%20%2B%201%3B%0A%7D%0Aint%20main%28%29%20%7B%0A%20%20unsigned%20returned_number_of_words%20%3D%20get_number_of_words%28%22these%20are%204%20words%22%29%3B%0A%7D&cumulative=false&curInstr=0&heapPrimitives=nevernest&mode=display&origin=opt-frontend.js&py=c_gcc9.3.0&rawInputLstJSON=%5B%5D&textReferences=false
unsigned get_number_of_words(const char *input_line) {
    const char *pointer = strchr(input_line, ' ');
    unsigned number_of_words = 0;

    while(pointer) {
        ++number_of_words;

        // Jump over ' ' and go to next ' '
        ++pointer;
        pointer = strchr(pointer, ' ');
    }

    // Words are the number of spaces + 1
    return number_of_words + 1;
}

LINE process_line(const char *input_line) {
    LINE line;
    
    // Populate line fields
    strcpy(line.text, input_line);
    line.size = strlen(input_line);
    line.number_of_words = get_number_of_words(input_line);

    return line;
}

// 2. Process all lines into a struct text

typedef struct text {
    LINE lines[MAXIMUM_LINES];
    unsigned number_of_lines;
}TEXT;

TEXT read_lines(FILE *f) {
    char line[MAXIMUM_CHARS_PER_LINE];
    TEXT text;

    text.number_of_lines = 0;

    while(fgets(line, MAXIMUM_CHARS_PER_LINE, f)) {
        text.lines[text.number_of_lines] = process_line(line);
        ++text.number_of_lines;
    }

    return text;
}

void print_text(TEXT text) {
    for(unsigned i = 0; i < text.number_of_lines; ++i) {
        printf("\nLINE #%d:\n", i);
        printf("\tText: %s", text.lines[i].text);
        printf("\tSize of line: %u\n", text.lines[i].size);
        printf("\tNumber of words: %u\n", text.lines[i].number_of_words);
    }
    printf("#################\n");
}

// 3. Sort lines based on criteria

int compare_lines(const void *a, const void *b) {
    LINE line_a = *(LINE*)a;
    LINE line_b = *(LINE*)b;

    if(line_a.size != line_b.size) {
        // Sort based on size (increasing)
        return line_a.size - line_b.size;
    } else {
        if(line_a.number_of_words != line_b.number_of_words) {
            // Sort based on number of words (decreasing)
            return line_b.number_of_words - line_a.number_of_words;
        } else {
            // Sort alphabetically
            return strcmp(line_a.text, line_b.text);
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        throw_error("Not enough arguments");
    }

    FILE *input_file = open_file(argv[1]);
    TEXT text = read_lines(input_file);
    qsort(text.lines, text.number_of_lines, sizeof(LINE), compare_lines);
    print_text(text);

    close_file(input_file);

    return 0;
}