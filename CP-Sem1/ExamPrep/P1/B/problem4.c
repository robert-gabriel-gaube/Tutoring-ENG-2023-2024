#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#define CHUNK_SIZE 10
#define MAX_PAIRS 100

/*
    Explanations:
        So I assume that key=value is correct on every line and that every
        line is arbitrary long, therefore we need to read in chunks and 
        store the values in a key value pair.

        My thinking process is like this:
            - We read chunks of a line until we read a '\n' or we reach 
                EOF (in which case we return a empty PAIR)
            - If a chunk contains '=' append the chars from start of chunk
                until '=' into key (if they exist) and from '=' to the end 
                of chunk to the value (if they exist).
            - If it doesn't contain '=' append to key or value, 
                if we didn't find '=' yet, append to key
                else, append to value
            - After that sort and print
*/

typedef enum {
    key, 
    value
}FIELD;

typedef struct {
    unsigned key_length, value_length;
    char *key, *value;
}PAIR;

typedef struct {
    PAIR pairs[MAX_PAIRS];
    int number_of_pairs;
}DICT;

// General functions

FILE *process_args(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage ./program <input_path>");
        exit(EXIT_FAILURE);
    }
    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        perror("Error while opening file.");
        exit(EXIT_FAILURE);
    }
    return f;
}
void close_file(FILE *f) {
    if(fclose(f) == EOF) {
        perror("Error while closing file");
        exit(EXIT_FAILURE);
    }
}
char last_char_of_string(char *chunk) {
    return chunk[strlen(chunk) - 1];
}
int compare_pairs(const void *p1, const void *p2) {
    PAIR* pair1 = (PAIR*)p1;
    PAIR* pair2 = (PAIR*)p2;

    int compare_result = strcmp(pair1->key, pair2->key);
    if(compare_result != 0) {
        return compare_result;
    } else {
        return strcmp(pair1->value, pair2->value);
    }
}
void print_pairs(DICT dict) {
    for(int idx = 0; idx < dict.number_of_pairs; ++idx) {
        printf("PAIR #%d: (%s) = (%s)\n", idx, dict.pairs[idx].key, dict.pairs[idx].value);
    }
    printf("\n");
}
void dealloc_dict(DICT dict) {
    for(int idx = 0; idx < dict.number_of_pairs; ++idx) {
        free(dict.pairs[idx].key);
        free(dict.pairs[idx].value);
    }
}

// Problem solving functions

// Make additional space into key or value based on the value of field 
// and return the changed pair
PAIR make_additional_space(PAIR pair, int extra, FIELD field) {
    int field_length = 0;
    char *field_pointer = NULL;

    // Extract the needed field
    if(field == key) {
        field_length = pair.key_length;
        field_pointer = pair.key;
    } else {
        field_length = pair.value_length;
        field_pointer = pair.value;
    }

    // Reallocate for extra space
    // + 1 for '\0'
    int total_number_of_chars = field_length + extra + 1;
    char *aux = realloc(field_pointer, total_number_of_chars * sizeof(char));
    if(aux == NULL) {
        perror("Problem with allocating memory");
        exit(EXIT_FAILURE);
    }
    field_pointer = aux;

    // if field_length is 0 we need to place a '\0' into the string
    // the rest of the times strcat will take care of that '\0'
    if(field_length == 0) {
        field_pointer[0] = '\0';
    }

    // Place new values in pair
    // - 1 because we don't count '\0'
    if(field == key) {
        pair.key = field_pointer;
        pair.key_length = total_number_of_chars - 1;
    } else {
        pair.value = field_pointer;
        pair.value_length = total_number_of_chars - 1;
    }

    return pair;
}

PAIR process_line(FILE *input) {
    // Initialize pair with default values
    PAIR pair = {0, 0, NULL, NULL};

    // Give a default value to chunk so it can enter the while
    char chunk[CHUNK_SIZE] = "aux";

    bool concat_into_key = true;

    while(last_char_of_string(chunk) != '\n') {
        // If we get to EOF return pair with default values
        if(fgets(chunk, CHUNK_SIZE, input) == NULL) {
            return pair;
        }

        char *equal = strchr(chunk, '=');
        // If we find a '=' in our chunk
        if(equal != NULL) {
            concat_into_key = false;

            // Copy into key from start until equal if '=' is not the first char
            if(equal != chunk) {
                int number_of_characters = equal - chunk;
                pair = make_additional_space(pair, number_of_characters, key);
                strncat(pair.key, chunk, number_of_characters);
                pair.key[pair.key_length] = '\0';
            }

            // Copy into value from equal + 1 until the end if '=' is not the last char
            if(last_char_of_string(chunk) != '=') {
                pair = make_additional_space(pair, strlen(equal + 1), value);
                strcpy(pair.value, equal + 1);
            }

        } else {
            // If there's not an equal in chunk just append chunk into a field

            if(concat_into_key) {
                pair = make_additional_space(pair, CHUNK_SIZE - 1, key);
                strcat(pair.key, chunk);
            } else {
                pair = make_additional_space(pair, CHUNK_SIZE - 1, value);
                strcat(pair.value, chunk);
            }
        }
    }

    // Replace '\n' from the end with '\0'
    pair.value[strcspn(pair.value, "\n")] = '\0';

    return pair;
}

DICT process_lines(FILE *input) {
    DICT dict;
    dict.number_of_pairs = 0;

    PAIR pair = process_line(input);

    // Add all the pairs to a dictionary
    while(pair.key_length != 0) {
        dict.pairs[dict.number_of_pairs] = pair;
        ++dict.number_of_pairs;

        pair = process_line(input);
    }

    return dict;
}

void print_sorted(FILE *input) {
    DICT dict = process_lines(input);
    qsort(dict.pairs, dict.number_of_pairs, sizeof(PAIR), compare_pairs);
    print_pairs(dict);
    dealloc_dict(dict);
}
int main(int argc, char *argv[]) {
    FILE *input = process_args(argc, argv);

    print_sorted(input);

    close_file(input);
    return 0;
}