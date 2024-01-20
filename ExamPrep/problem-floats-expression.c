/*
    Implement a function that receives a string representing an arithmetic expression consisting only of additions
    and subtractions of floating point numbers (in any C format) and returns the values of the expression. 
    Deviations from the format shall be handled as errors.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Put float term in term_location and return the address after the read number
const char *get_term(float *term_location, const char *expression) {
    // Verify that pointer points to a digit aka start of a number
    if(!isdigit(*expression)) {
        if(*expression == '\0') {
            printf("Reached end of string unexpectedly\n");
        } else { 
            printf("Unexpected character when trying to read number '%c'\n", *expression);
        }
        exit(-1);
    }

    char *end_of_number = NULL;
    *term_location = strtof(expression, &end_of_number);

    return end_of_number;
}

float evaluate_expression(const char *expression) {
    float result = 0, right_hand_term = 0;
    // Initialise result with the first term
    expression = get_term(&result, expression);

    while(*expression != '\0') {
        switch(*expression) {
            case '+':
                // Jump over '+';
                ++expression; 

                expression = get_term(&right_hand_term, expression);
                result += right_hand_term;
            break;
            case '-':
                // Jump over '-';
                ++expression; 

                expression = get_term(&right_hand_term, expression);
                result -= right_hand_term;
            break;
            default:
                printf("Unexpected operand '%c'\n", *expression);
                exit(-1);
        }
    }
    return result;
}

int main() {
    float result = evaluate_expression("12.10+3.20-0.30+5+10.50-0.50 ");
    printf("%f\n", result);
    return 0;
}