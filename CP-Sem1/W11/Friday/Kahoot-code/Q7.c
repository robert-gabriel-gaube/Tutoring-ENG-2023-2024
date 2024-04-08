#include <stdio.h>

void arr_op(int *arr, int size) {
    for(int *idx = arr; idx - arr < size; ++idx) {
        printf("%d ", *idx); // In question it was idx not *idx
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4};
    arr_op(arr, 4);
    return 0;
}