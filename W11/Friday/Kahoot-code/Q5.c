#include <stdio.h>

void f(char **sp) {
    *sp = "mama";
}

int main() {
    char *s = "abc";
    f(&s);
    printf("%s\n", s); // mama

    return 0;
}