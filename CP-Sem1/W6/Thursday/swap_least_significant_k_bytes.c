#include <stdio.h>

/* 

    Plan for solving problem 8

    1. Create a function to extract byte at a specific position
    TESTING
    2. Create a function ot set the byte of a specific position 
        - This function works as expected if the range of the byte in n is 0x00
            * For example if we want to set k = 3, n = 0x00123456, the result will be correct only if we set byte number 3
        - We'll leave the reseting of bits up to the programmer 
            * For example if we want to set k = 2, n = 0x00123456, the result will be correct only if we set byte number 2 in n to 0 first and the use or
    TESTING
    3. Test if k is at a valid position and add or change in 1. and 2.
    TESTING
    4. Create function to swap endianness
    TESTING
    5. Create function to add the rest of the unchanged bits
    TESTING

*/

// 3.
int is_position_valid(unsigned size, unsigned position) {
    if(position >= size) { // Indexing starts from 0
        printf("[WARNING] Position is out of range.\n");
        return 0;
    }
    return 1;
}

// 1.
unsigned extract_byte(unsigned number, unsigned position) {
    // On wrong position return unchanged number
    if(is_position_valid(sizeof(number), position) == 0) return number;
    return (number >> (position * 8)) & 0xFF;
}

// 2.
unsigned set_byte(unsigned number, unsigned position, unsigned byte) {
    // On wrong position return unchanged number
    if(is_position_valid(sizeof(number), position) == 0) return number;
    return (number | (byte << (position * 8)));
}

// 5.
unsigned set_unchanged_bytes(unsigned answer, unsigned k, unsigned n) {
    if(k < sizeof(n)) {
        answer = answer | (n &  (~0u << k * 8));
    }
    return answer;
}

// 4.
unsigned swap_endianness_of_k_bytes(unsigned n, unsigned k) {
    unsigned start = 0, end = k - 1;
    unsigned answer = 0;
    while(start <= end) {
        unsigned start_byte = extract_byte(n, start);
        unsigned end_byte = extract_byte(n, end);

        answer = set_byte(answer, start, end_byte);
        answer = set_byte(answer, end, start_byte);

        ++start; --end;
    }
    
    answer = set_unchanged_bytes(answer, k, n);

    return answer;
}

void test() {
    printf("Testing position checking\n");

    printf("%s\n", is_position_valid(4, 0) ? "it's valid" : "it's not valid"); // it's valid
    printf("%s\n", is_position_valid(4, 1) ? "it's valid" : "it's not valid"); // it's valid
    printf("%s\n", is_position_valid(4, 2) ? "it's valid" : "it's not valid"); // it's valid
    printf("%s\n", is_position_valid(4, 3) ? "it's valid" : "it's not valid"); // it's valid
    printf("%s\n", is_position_valid(4, 4) ? "it's valid" : "it's not valid"); // it's not valid and warning message
    printf("%s\n", is_position_valid(4, 10) ? "it's valid" : "it's not valid"); // it's not valid and warning message

    printf("Testing extract byte \n");

    printf("0x%X\n", extract_byte(0xABCDEF12, 0)); // 0x12
    printf("0x%X\n", extract_byte(0xABCDEF12, 1)); // 0xEF
    printf("0x%X\n", extract_byte(0xABCDEF12, 2)); // 0xCD
    printf("0x%X\n", extract_byte(0xABCDEF12, 3)); // 0xAB
    printf("0x%X\n", extract_byte(0xABCDEF12, 4)); // 0xABCDEF12 and warning message

    printf("Testing set byte \n");

    unsigned n = 0;
    printf("0x%X\n", n = set_byte(n, 3, 0xAB)); // 0xAB000000
    printf("0x%X\n", n = set_byte(n, 0, 0x12)); // 0xAB000012
    printf("0x%X\n", n = set_byte(n, 2, 0xCD)); // 0xABCD0012
    printf("0x%X\n", n = set_byte(n, 1, 0xEF)); // 0xABCDEF12
    printf("0x%X\n", n = set_byte(n, 5, 0x00)); // 0xABCDEF12 and warning message

    printf("Testing swap endianess\n");

    printf("0x%X\n", swap_endianness_of_k_bytes(0x12345678, 3)); //0x12785634
    printf("0x%X\n", swap_endianness_of_k_bytes(0x12345678, 2)); //0x12347856
    printf("0x%X\n", swap_endianness_of_k_bytes(0x12345678, 4)); //0x78563412
}
int main() {
    test();
    return 0;
}