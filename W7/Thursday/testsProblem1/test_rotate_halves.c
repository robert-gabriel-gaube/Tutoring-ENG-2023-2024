#include "../problem1.h"
#include <assert.h>
#include <stdio.h>

int main() {
    unsigned passed = 0, total = 8;

    unsigned numbers[4] = {0x12344321, 0x12000012, 0x43211234, 0xAAAABBBB};
    for(int idx = 0; idx < sizeof(unsigned); ++idx) {
        printf("\n\nTesting rotate_halves on number 0x%X\n", numbers[idx]);

        unsigned value = rotate_halves(numbers[idx]);
        if(value == (((numbers[idx] << 4) >> 8) << 4)) {
            printf("\t[PASSED] rotate_halves(number) == 0x0%X\n", value);
            passed++;
        } 
        else {
            printf("\t[FAILED] rotate_halves(number) == 0x%X (Expected 0x0%x)\n", value, ((numbers[idx] << 4) >> 8) << 4);
        }
    }

    printf("%d out of %d tests PASSED\n", passed, total);
    return 0;
}