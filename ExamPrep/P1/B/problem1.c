#include <stdio.h>
#include <stdbool.h>
#define BIG_VALUE 0x7FFFFFFF

int isodigit(char c) {
    return (c >= '0' && c <= '7');
}

int digit_value(char c) {
    return c - '0';
}

int read_number() {
    char current_char = getchar();
    int num = 0;

    while(isodigit(current_char)) {
        num = num * 10 + digit_value(current_char);
        current_char = getchar();
    }

    // Put last character back to be checked by read_input
    ungetc(current_char, stdin);

    return num;
}

int oct_to_dec(int number) {
    if(number) {
        return number % 10 + 8 * oct_to_dec(number / 10);
    } else {
        return 0;
    }
}

void print_values(int num_numbers, int min, int max) {
    if(num_numbers) {
        printf("Num numbers: %d, where min: %X, and max: %X\n", num_numbers, min, max);
    } else {
        printf("No valid numbers on this line\n");
    }
}

void read_input() {
    bool is_last_char_a_valid_separator = true;
    char current_char;
    int min = BIG_VALUE, max = 0, num_numbers = 0;

    while((current_char = getchar()) != EOF) {
        if(is_last_char_a_valid_separator && isodigit(current_char)) {
            // Put digit back to be read by read_number
            ungetc(current_char, stdin);

            int number = read_number();

            // Test if valid separator after
            current_char = getchar();

            if(current_char == ' ' || current_char == EOF || current_char == '\n') {
                // Is valid number
                ++num_numbers;
                number = oct_to_dec(number);

                max = number > max ? number : max;
                min = number < min ? number : min;

                // End of line
                if(current_char == '\n') {
                    print_values(num_numbers, min, max);
                    min = BIG_VALUE, max = 0, num_numbers = 0;
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
            print_values(num_numbers, min, max);
            min = BIG_VALUE, max = 0, num_numbers = 0;
        }
    }

}

int main() {
    read_input();
    return 0;
}