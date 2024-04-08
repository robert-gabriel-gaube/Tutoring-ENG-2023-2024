#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

char *find_next_digit(char *s) {
    int number_of_positions = strcspn(s, "0123456789");
    return s + number_of_positions;
}

// Verify if number is at beginning, end or delimited by ' '
bool is_valid_number(char *base, char *start_number, char *end_number) {
    if(!(*end_number == ' ' || *end_number == '\0')) {
        return false;
    }
    if(start_number == base) {
        return true;
    } else if(*(start_number - 1) != ' ') {
        return false;
    }
    return true;
}

int read_ints(char *s, int ints[], int capacity) {
    long number;
    int idx_ints = 0;
    char *end_address, *string_pointer = s;

    string_pointer = find_next_digit(string_pointer);

    while(*string_pointer && idx_ints < capacity) {
        number = strtol(string_pointer, &end_address, 10);

        if(is_valid_number(s, string_pointer, end_address)) {
            // Put into array
            ints[idx_ints] = number;
            ++idx_ints;
        }

        string_pointer = find_next_digit(end_address);
    }
    
    return idx_ints;
}

int main() {
    char example[] = "1 ana are 12 mere, 29.5 prune si 14 portocale 23";
    int numbers[3], capacity = 3;
    int written_nums = read_ints(example, numbers, capacity);

    for(int idx = 0; idx < written_nums; ++idx) {
        printf("%d ", numbers[idx]);
    }
    printf("\n");
    return 0;
}