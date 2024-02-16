/*
    Implement a C function that will find, search and replace text strings. 
    Receives three strings (s1, s2 and s3) and replaces all the occurrences 
    of string s2 into the first string (s1), with the third string (s3),
    returning the new string. The replacement phrase can be shorter or longer
    than the searched for phrase. Show the updated initial line of text on the display.

    Example:
        s1 = one two one two three
        s2 = one 
        s3 = five
        => s1 = five two five two three

        s1 = five two five two three
        s2 = five 
        s3 = one 
        => s1 = one two one two three
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 100

void make_space(char *location, unsigned no_spaces) {
    char *aux = strdup(location);

    strcpy(aux, location);
    strcpy(location + no_spaces, aux);
    free(aux);
}

void erase_space(char *location, unsigned no_spaces) {
    char *aux = strdup(location);

    strcpy(aux, location + no_spaces);
    strcpy(location, aux);
    free(aux);
}

void replace_occurences(char s1[], char s2[], char s3[]) {
    char *ptr = s1;
    char *occurence = strstr(s1, s2);
    unsigned no_spaces;

    if(strlen(s2) > strlen(s3)) {
        no_spaces = strlen(s2) - strlen(s3);
    } else {
        no_spaces = strlen(s3) - strlen(s2);
    }

    while(occurence != NULL) {
        if(strlen(s2) > strlen(s3)) {
            erase_space(occurence, no_spaces);
        } else if(strlen(s2) < strlen(s3)) {
            make_space(occurence, no_spaces);
        }
        strncpy(occurence, s3, strlen(s3));

        ptr = occurence + strlen(s3);
        occurence = strstr(ptr, s2);
    }
}

int main() {
    char s1[MAX_LEN] = "one two one two three";
    char s2[] = "one";
    char s3[] = "twone";

    replace_occurences(s1, s2, s3);

    printf("S1 after replace: %s\n", s1);
    return 0;
}
