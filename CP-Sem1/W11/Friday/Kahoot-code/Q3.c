#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3};
    int *p = arr;

    *p = 3;
    p += 2;
    *p = 1;
    
    printf("%d %d %d\n", arr[0], arr[1], arr[2]);
    // 3 2 1
    return 0;
}