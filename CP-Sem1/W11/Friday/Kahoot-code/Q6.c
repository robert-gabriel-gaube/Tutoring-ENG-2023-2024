#include <stdio.h>
#define ARR_SIZE 4

int *arr_search(int arr[], int size, int value_searched) {
    for(int idx = 0; idx < size; ++idx) {
        if(arr[idx] == value_searched) {
            return arr + idx;
        }
    }
    return NULL;
}

int main() {
    int arr[ARR_SIZE] = {1, 2, 3, 4};
    printf("%ld\n", arr_search(arr, ARR_SIZE, 3) - arr); // 2

    return 0;
}