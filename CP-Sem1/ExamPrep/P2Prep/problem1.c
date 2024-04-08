/*
    Read a directory structure with possible subdirectories and 
    print the total size of all directories
    Input:
        dir documents ( 2048 512 ) dir photos ( 3072 dir summer ( 2048 1024 ) )
    Output:
        documents: 2560
        photos: 6144
        summer: 3072
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

long process_directory() {
    // Read dir name
    char dir_name[50];
    scanf("%50s", dir_name);

    char token[50];
    // Read '(', we won't use it
    scanf("%50s", token);

    scanf("%50s", token);
    long count = 0;

    // While we have token in current dir
    while(strcmp(token, ")") != 0) {
        // If dir recursive call
        if(strcmp(token, "dir") == 0) {
            count += process_directory();
        } else {
            // Transform to number and count it
            count += strtol(token, NULL, 10);
        }
        // Go to next token
        scanf("%50s", token);
    }
    // Print dir size
    printf("%s : %ld\n", dir_name, count);
    return count;
}

int main() {
    char word[50];
    int read_status = scanf("%50s", word);
    
    // While we have other dirs and we have input left to read
    while(strcmp(word, "dir") == 0 && read_status == 1) {
        process_directory();
        read_status = scanf("%50s", word);
    }
    return 0;
}