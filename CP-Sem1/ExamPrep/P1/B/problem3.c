#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int number_of_digits(int number) {
    int num = 0;
    while(number) {
        number /= 10;
        ++num;
    }
    return num;
}

void replace_with_number(char *format, int number) {
    // Transform from int to string
    char number_string[20];
    sprintf(number_string, "%d", number);

    // Place number in the allocated space
    for(size_t idx = 0; idx < strlen(number_string); ++idx) {
        format[idx] = number_string[idx];
    }
}

void mysprintf(char *format, int elements[], int number_of_elements) {
    // Make an auxiliary string the same space as format
    char *aux = strdup(format);

    // Used for the current element to be replaced into format
    int element_idx = 0;
    // Go to next %d in format
    format = strstr(format, "%d");

    while(element_idx < number_of_elements && format != NULL) {
        // Find the number of digits of the next to be replaced number into %d
        int size_of_replacement = number_of_digits(elements[element_idx]);

        // Make space for the new number
        if(size_of_replacement != 1) {
            // Add spaces for extra characters
            strcpy(aux, format);
            strcpy(format + size_of_replacement - 2, aux);
        } else {
            // Remove one character
            strcpy(aux, format + 1);
            strcpy(format, aux);
        }

        // Place the number there
        replace_with_number(format, elements[element_idx]);

        // Go to next %d in format
        format = strstr(format, "%d");
        
        // Go to next number
        ++element_idx;
    }
    free(aux);
}

int main() {
    int numbers[4] = {1, 22, 333, 4444};
    char s[100] = "%dAna are %d mere si %d pere si %d banane.%d";
    mysprintf(s, numbers, 4);
    printf("%s\n", s);
    return 0;
}