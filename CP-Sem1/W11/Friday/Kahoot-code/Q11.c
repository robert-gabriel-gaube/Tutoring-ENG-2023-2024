#include <stdio.h>
int main() {
    int a = 0;
    char *x = (char *) &a;

    x[0] = 1;
    x[1] = 2;

    printf("%d\n", a); 
    // 513

    return 0;
}