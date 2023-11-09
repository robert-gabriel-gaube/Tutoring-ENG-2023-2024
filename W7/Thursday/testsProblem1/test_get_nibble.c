#include "../problem1.h"
#include <assert.h>
#include <stdio.h>

int main() {
    unsigned number = 0x76543210, passed = 0, total = 8;
    printf("Testing get_nibble on number 0x%x\n", number);

    for(int idx = 0; idx < sizeof(number) * 2; ++idx) {
        int value = get_nibble(number, idx);
        if(idx == value) {
            printf("\t[OK] get_nibble(number, %d) == %d\n", idx, value);
            ++passed;
        } else {
            printf("\t[FAILED] get_nibble(number, %d) == %d (EXPECTED VALUE: %d)\n", idx, value, idx);    
            
        }
    }

    printf("%d out of %d tests PASSED\n", passed, total);
    return 0;
}