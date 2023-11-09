#include "../problem1.h"
#include <assert.h>
#include <stdio.h>

// Run 'make test_get_nibble' after implementation
unsigned t_get_nibble(unsigned number, unsigned nibblePosition) {
    return (number >> (nibblePosition * 4)) & 0xF;
}
// Run 'make test_rotate_halves' after implementation
unsigned t_rotate_halves(unsigned number) {
    return (((number >> 4) & 0xFFFF0000) | ((number << 4) & 0xFFFF));
}
// Run 'make test_set_nibble' after implementation
unsigned t_set_nibble_at_position(unsigned number, unsigned nibble, unsigned nibblePosition) {
    return number | (nibble << nibblePosition * 4);
}


// Decomment this after implementing the above functions
// Run command 'make test_rotate_nibbles' after decomenting
unsigned t_rotate_middle_nibbles(unsigned number) {
    unsigned centralNibbleLeft = t_get_nibble(number, 4);
    unsigned centralNibbleRight = t_get_nibble(number, 3);

    number = t_rotate_halves(number);

    number = t_set_nibble_at_position(number, centralNibbleLeft, 7);
    number = t_set_nibble_at_position(number, centralNibbleRight, 0);

    return number;
}

int main() {
    unsigned passed = 0, total = 4;

    unsigned numbers[4] = {0x12344321, 0x41233214, 0x34122143, 0x23411432};
    for(int idx = 0; idx < sizeof(unsigned); ++idx) {
        printf("\n\nTesting rotate_middle_nibbles on number 0x%X\n", numbers[idx]);

        unsigned value = rotate_middle_nibbles(numbers[idx]);
        if(value == t_rotate_middle_nibbles(numbers[idx])) {
            printf("\t[PASSED] rotate_middle_nibbles(number) == 0x%X\n", value);
            passed++;
        } 
        else {
            printf("\t[FAILED] rotate_middle_nibbles(number) == 0x%X (Expected 0x%x)\n", value, t_rotate_middle_nibbles(numbers[idx]));
        }
    }

    printf("%d out of %d tests PASSED\n", passed, total);
    return 0;
}