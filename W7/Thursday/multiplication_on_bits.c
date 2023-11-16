#include <stdio.h>

unsigned get_bit(unsigned n, unsigned k) {
    return (n >> k) & 1;
}
unsigned set_bit(unsigned n, unsigned k) {
    return n | (1 << k);
}

unsigned add_on_bits(unsigned a, unsigned b) {
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

/*

nr1 = 58       111010 *
nr2 = 5;          101 
              --------
               111010
              000000
             111010
             ---------
            100100010


*/

unsigned int multiply_on_bits(unsigned int nr1, unsigned int nr2){
    unsigned int result=0;
    unsigned int k=0;
    
    while(nr2>0){
        unsigned int bit= nr2 & 1; //taking the least significant bit of the second nr 
        if(bit==1){ // we add only if nr2's bit==1, if it's not we just increment k and take the second bit 
            result= add_on_bits(result, nr1 << k); // <=>  result = result + (nr1 << k);
        }
        nr2= nr2 >> 1; //we RShift so we can get the following bit of nr2
        k++;
        
    }
    
    return result; 
}



int main()
{
   int nr1=0b111010;  //58 
   int nr2=0b000101;  //5
   printf("Multiplication of 58 & 5 is: %d \n", multiply_on_bits(nr1,nr2)); //290
   
   int nr3=0b101011;  //43 
   int nr4=0b1110;  //14
   printf("Multiplication on 43 & 14 is: %d", multiply_on_bits(nr3,nr4)); //602 
   
    return 0;
}
