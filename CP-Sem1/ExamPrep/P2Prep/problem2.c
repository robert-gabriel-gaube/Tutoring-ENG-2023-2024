/*
    Implement a function that takes in a uint32_t number and returns 
    the maximum number that cand be obtained by rotating the number to the right.
    Input: 
        0x0000000F
    Output:
        0xF0000000
*/

#include <stdint.h>
#include <stdio.h>

int max_rot_R(uint32_t number) {
    uint32_t max_num = number;
    for(int i = 0; i < 32; ++i) {
        // Get most significant bit and put it on position 0
        number = ((number & 0x80000000) >> 31) | (number << 1);

        // Save biggest number
        max_num = number > max_num ? number : max_num;
    }
    return max_num;
}

int main() {
    return 0;
}