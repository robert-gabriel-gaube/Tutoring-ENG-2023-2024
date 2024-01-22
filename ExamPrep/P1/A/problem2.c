#include <stdio.h>
#include <stdint.h>

// Credits to Mr. Minea :)
uint32_t collate_numbers(uint32_t a, uint32_t b) {
    return (a & 0x0F0F0F0F) | (b & 0xF0F0F0F0);
}

int main() {
    printf("%X\n", collate_numbers(0xA1B2C3D4, 0x11223344));
    return 0;
}