#include <stdio.h>

/* 
	Every other bit Write a function that takes a 
	32-bit unsigned and returns the 16-bit number 
	formed by the bits in even positions. 
*/

int main(){
	
	// pos 0 from n -> pos 0 from r
	// pos 2 from n -> pos 1 from r
	// pos 4 from n -> pos 2 from r
	// pos idx from n -> pos idx / 2 from r

	unsigned n = 0xAAAAAAAA;
	unsigned r = 0;

	for(int idx = 0; idx < sizeof(unsigned) * 8; idx += 2) {
		unsigned bit_from_number = (n >> idx) & 1;
		unsigned pos_r = idx / 2;
		r = r | (bit_from_number << pos_r);
	}
	printf("0x%X\n", r);

	return 0;
}