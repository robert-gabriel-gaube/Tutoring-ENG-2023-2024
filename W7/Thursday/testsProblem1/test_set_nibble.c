#include "../problem1.h"
#include <assert.h>
#include <stdio.h>

int main() {
    unsigned passed = 0, total = 8;
    unsigned numbers[10] = {0xABCDEF01, 0xABCDEF00, 0xABCDE000, 0xABCD0000, 0xABC00000, 0xAB000000, 0xA0000000, 0x00000000};

    unsigned setting_val = 10;
    for(int idx = sizeof(unsigned) * 2 - 1; idx >= 0; --idx) {
        printf("\n\nTesting set_nibble on number 0x%X\n", numbers[idx]);
        unsigned value = set_nibble_at_position(numbers[idx], setting_val, idx);

        if(value == (numbers[idx] | (setting_val << idx * 4))) {
            printf("\t[PASSED] set_nibble_at_position(number, 0x%X, %d) == 0x%X\n", setting_val, idx, value);
            passed++;
        } 
        else {
            printf("\t[FAILED] set_nibble_at_position(number, 0x%X, %d) == 0x%X, (EXPECTED VALUE: 0x%X)\n", setting_val, idx, value, (numbers[idx] | (setting_val << idx * 4)));
        }
        setting_val = (setting_val + 1) % 16;
    }

    printf("%d out of %d tests PASSED\n", passed, total);
    return 0;
}