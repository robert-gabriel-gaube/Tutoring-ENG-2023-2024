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
    char dir_name[50];
    scanf("%50s", dir_name);

    char token[50];
    scanf("%50s", token);
    scanf("%50s", token);

    long count = 0;
    while(strcmp(token, ")") != 0) {
        if(strcmp(token, "dir") == 0) {
            count += process_directory();
        } else {
            count += strtol(token, NULL, 10);
        }
        scanf("%50s", token);
    }
    printf("%s : %ld\n", dir_name, count);
    return count;
}

int main() {
    char word[50];
    int read_status = scanf("%50s", word);
    
    
    while(strcmp(word, "dir") == 0 && read_status == 1) {
        process_directory();
        read_status = scanf("%50s", word);
    }
    return 0;
}