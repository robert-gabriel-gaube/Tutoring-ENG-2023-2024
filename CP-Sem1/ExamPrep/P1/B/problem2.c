#include <stdio.h>
#include <stdint.h>

uint64_t get_max_complemented(uint64_t n, uint8_t k) {
    // Mask of k consecutive ones
    uint64_t mask = ~(((-1) << k));

    uint64_t max = n;
    for(uint8_t idx = 0; idx <= 64 - k; ++idx) {
        uint64_t new_num = n ^ mask;

        max = new_num > max ? new_num : max;

        mask <<= 1;
    }

    return max;
}

int main() {
    printf("%lX\n", get_max_complemented(0xF, 4));
    return 0;
}