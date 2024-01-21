/*
    Run-Length Encoding (RLE) is a simple form of data compression where consecutive elements of 
    the data that are the same are replaced with a single value and the count of occurrences. 
    
    In this problem, you are required to implement a C function that encodes a C-style string 
    given as a parameter into its RLE form.

    aaabbbcc -> a3b3c2

    string will be at most 500 chars. (before and after compression)
*/

#include <stdio.h>
#include <string.h>

void rl_encoding(char *s) {
    char encoded_string[500];
    unsigned count = 1, string_len = 0; 

    for(unsigned idx = 0; idx < strlen(s); ++idx) {
        if(s[idx] == s[idx + 1]) { // If we have the same character
            ++count;
        } else {
            // Put the encoded substring into encoded_string
            // and add the \0 terminator
            encoded_string[string_len] = s[idx];
            encoded_string[string_len + 1] = count + '0';
            encoded_string[string_len + 2] = '\0';

            // Increment value and reset count
            string_len += 2;
            count = 1;
        }
    }

    // Copy result into original string
    strcpy(s, encoded_string);
}

int main() {
    char s[100] = "aaabbbccd";
    printf("BEFORE: %s\n", s);
    rl_encoding(s);
    printf("AFTER: %s\n", s);

    return 0;
}