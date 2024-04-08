#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    sn = sn-1|sn-2
    s0 = 0
    s1 = 01
    s2 = 01|0
    s3 = 010|01

*/
void verify_pointer(char *s) {
    if(s == NULL) {
        printf("Not enough space");
        exit(1);
    }
}

char *fibo_string(int n) {
    if(n == 0) {
        char *s0 = malloc(sizeof(char) * 2);
        verify_pointer(s0);
        s0[0] = '0', s0[1] = 0;
        return s0;
    }
    else if(n == 1) {
        char *s1 = malloc(sizeof(char) * 3);
        verify_pointer(s1);
        s1[0] = '0', s1[1] = '1', s1[2] = 0;
        return s1;
    }
    else {
        char *sn1 = fibo_string(n - 1);
        char *sn2 = fibo_string(n - 2);

        char *aux = realloc(sn1, strlen(sn1) + strlen(sn2) + 1);
        if(aux == NULL) {
            free(sn1);
            printf("Error with realloc\n");
            exit(1);
        }
        sn1 = aux;

        strcat(sn1, sn2);
        free(sn2);

        return sn1;
    }
}

int main() {
    while(1) {
        int x;
        scanf("%d", &x);
        char *s = fibo_string(x);
        printf("\n%s\n", s);
        free(s);
    }
    return 0;
}
/*
    fibo(2) -> strcat(fibo(1), fibo(0)); 
    fibo(1) -> "01"
    fibo(0) -> "0"
    
*/