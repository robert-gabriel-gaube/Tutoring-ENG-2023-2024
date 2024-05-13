#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

    // Secret takes a parameter, a string as a password, if the password
    // is correct then it will return a pointer to a string 
    // which contains important information. You do know that 
    // if the password is correct then the string will start with
    // "Access granted:"

    // We don't know the password so we need to guess it
    // The password has some constraints:
    // 1. It has 7 characters
    // 2. It starts with a capital letter (Position 0)
    // 3. Characters on positions 1, 2, 3 are digits
    // 4. The rest of the characters can be any digit or lowercase/uppercase letter

    const char *msg = secret("randompass");
    printf("Got message: %s\n", msg);

    // The secret data is encrypted using a Hill Cypher with a 2x2 matrix key
    // the key is unknown but we know that the decription key has some
    // constraints 

    // Hill cipher works by multiplying the message transformed into a vector of numbers
    // by the key matrix and then taking the modulo 26 of the result and transforming it back
    // into characters

    // The key is a 2x2 matrix with integer values
    // 1. The values at positions 0, 0 and 1, 1 are between 15 - 24
    // 2. The values at positions 0, 1 and 1, 0 are between 3 - 8

    int key[2][2] = {{19, 3}, {5, 24}};
    const char *decripted = hill_cypher_decript("HERE", key);
    printf("Decripted message: %s\n", decripted);

    // Tell me what you got from the secret and the decripted message

    return 0;
}