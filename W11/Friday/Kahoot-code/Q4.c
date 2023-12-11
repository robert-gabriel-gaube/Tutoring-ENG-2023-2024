#include <stdio.h>
#include <string.h>

int main() {
    const char *s = "abcde";
    const char *sp = s + 3;

    printf("%c ", sp[1]); // e
    printf("%ld\n", strchr(s, 'd') - s); // 3

    return 0;
}