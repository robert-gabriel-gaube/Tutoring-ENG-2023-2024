#include <stdio.h>
unsigned get_bit(unsigned n, unsigned k) {
    return (n >> k) & 1;
}
unsigned set_bit(unsigned n, unsigned k) {
    return n | (1 << k);
}

/*
    Result is initially 0
    Carry out is initially 0
    For every bit:
        Get bit from a at position bit_pos
        Get bit from b at position bit_pos
        Do bit from a + bit from b + carry_out
        if this sum doesn't generate carry out (sum < 2) then 
            Carry out is 0 
            if sum is 1 then
                Set bit in r at position bit_pos
        else
            Carry out is 1
            Subtract 2 from the sum (subtract the carry)
            if sum is 1 then 
                Set bit in r at position bit_pos
        
*/

unsigned add_on_bits_naive(unsigned a, unsigned b) {
    unsigned r = 0, carry_out = 0;

    for(unsigned bit_pos = 0; bit_pos < sizeof(a) * 8; ++bit_pos) {
        unsigned bit_a = get_bit(a, bit_pos);
        unsigned bit_b = get_bit(b, bit_pos);

        unsigned sum = bit_a + bit_b + carry_out;

        if(sum < 2) {
            carry_out = 0;
            if(sum == 1) {
                r = set_bit(r, bit_pos);
            }
        }
        else {
            carry_out = 1;
            sum -= 2;
            if(sum == 1) {
                r = set_bit(r, bit_pos);
            }
        }
    }
    return r;
}

/*
    We will base out solution on the following truth table:

    A | B | Cin || Sum | Cout
    ---------------------------
    0 | 0 | 0   ||  0  |  0
    0 | 0 | 1   ||  1  |  0
    0 | 1 | 0   ||  1  |  0
    0 | 1 | 1   ||  0  |  1
    1 | 0 | 0   ||  1  |  0
    1 | 0 | 1   ||  0  |  1
    1 | 1 | 0   ||  0  |  1
    1 | 1 | 1   ||  1  |  1

    From this table we see that we can express the outputs as follows:
    Sum = A ⊕ B ⊕ Cin - where ⊕ is XOR
    Cout = (A ∧ B) ∨ (B ∧ Cin) ∨ (A ∧ Cin) - where ∧ is AND, ∨ is OR
*/

unsigned add_on_bits_expressions(unsigned a, unsigned b) {
    unsigned r = 0, carry_out = 0;

    for(unsigned bit_pos = 0; bit_pos < sizeof(a) * 8; ++bit_pos) {
        unsigned bit_a = get_bit(a, bit_pos);
        unsigned bit_b = get_bit(b, bit_pos);

        unsigned r_bit = bit_a ^ bit_b ^ carry_out;
        carry_out = (bit_a & bit_b) | (bit_b & carry_out) | (bit_a & carry_out);

        if(r_bit == 1) {
            r = set_bit(r, bit_pos);
        }
    }
    return r;
}

void test() {
    printf("Testing naive solution\n");
    
    printf("%d\n", add_on_bits_naive(1, 3)); // 4 
    printf("%d\n", add_on_bits_naive(50, 150)); // 200
    printf("%d\n", add_on_bits_naive(111150, 150)); // 111300

    printf("\nTesting expressions solution\n");

    printf("%d\n", add_on_bits_expressions(1, 3)); // 4 
    printf("%d\n", add_on_bits_expressions(50, 150)); // 200
    printf("%d\n", add_on_bits_expressions(111150, 150)); // 111300
}   

int main() {
    test();
    return 0;
}