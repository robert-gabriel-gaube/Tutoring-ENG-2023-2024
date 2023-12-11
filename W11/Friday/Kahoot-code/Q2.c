#include <stdio.h>
void increment(int *px) {
    *px = *px + 1;
}

int main() {
    int num = 10;
    printf("%d ", num);
    increment(&num);
    printf("%d ", num);
    increment(&num);
    printf("%d\n", num);
    // 10 11 12
    return 0;
}