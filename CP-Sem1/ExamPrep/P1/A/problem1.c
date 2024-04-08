#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#define BIG_VALUE 0x7FFFFFFF

int digit_value(char c) {
    if(isdigit(c)) {
        return c - '0';
    } else {
        return toupper(c) - 'A' + 10;
    }
}

// Read and transform to decimal
int read_number() {
    char current_char = getchar();
    int num = 0;

    while(isxdigit(current_char)) {
        num = num * 16 + digit_value(current_char);
        current_char = getchar();
    }

    // Put last character back to be checked by read_input
    ungetc(current_char, stdin);

    return num;
}

void print_values(int num_numbers, float average, int max) {
    if(num_numbers) {
        printf("Num numbers: %d, where average: %f, and max: %d\n", num_numbers, average, max);
    } else {
        printf("No valid numbers on this line\n");
    }
}

void read_input() {
    bool is_last_char_a_valid_separator = true;
    char current_char;
    int max = 0, num_numbers = 0;
    float sum = 0;

    while((current_char = getchar()) != EOF) {
        if(is_last_char_a_valid_separator && isxdigit(current_char)) {
            // Put digit back to be read by read_number
            ungetc(current_char, stdin);

            int number = read_number();

            // Test if valid separator after
            current_char = getchar();

            if(current_char == ' ' || current_char == EOF || current_char == '\n') {
                // Is valid number
                ++num_numbers;

                max = number > max ? number : max;
                sum += number;

                // End of line
                if(current_char == '\n') {
                    print_values(num_numbers, sum / num_numbers, max);
                    num_numbers = 0, max = 0, sum = 0;
                    continue;
                } 
            } else {
                // Is not a valid separator
                is_last_char_a_valid_separator = false;
            }
        }
        is_last_char_a_valid_separator = (current_char == ' ');

        if(current_char == '\n') {
            is_last_char_a_valid_separator = true;
            print_values(num_numbers, sum / num_numbers, max);
            num_numbers = 0, max = 0, sum = 0;
        }
    }
}

int main() {
    read_input();
    return 0;
}