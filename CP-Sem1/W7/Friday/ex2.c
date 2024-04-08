/*
	Implement a function unsigned getMaxRotL(unsigned); which returns the minimum value which can be
	obtained by consecutively applying left-shift-rotate to the nibbles of the argument. Left-shift-rotate represents the operation
	in which the most significant nibble of the number is inserted in the position of the least significant one, the rest of the bits
	being shifted one position to the left. Test the function in main(), printing the result in hexadecimal.
*/

#include <stdio.h>
// returns nibble at position k (0 - (sizeof(n) - 1))
unsigned get_nibble(unsigned n, unsigned k) {
	return (n >> (k * 4)) & 0xF; //0xF = 0b1111
}

unsigned rotate_nibble_left(unsigned nibble) {
	unsigned ms_bit = (nibble >> 3) & 1;
	nibble = (nibble << 1) & 0xF;
	return nibble | ms_bit;
}

unsigned reset_nibble(unsigned n, unsigned pos_nibble) {
	return n & ~(0xF << (pos_nibble * 4));
}

unsigned set_nibble(unsigned n, unsigned pos_nibble, unsigned nibble) {
	return n | (nibble << (pos_nibble * 4));
}

unsigned rotate_nibbles_left(unsigned n) {
	for(int idx_nibbles = 0; idx_nibbles < sizeof(n) * 2; ++idx_nibbles) {
		// Get nibble at idx_nibbles
		// Rotate nibble
		// Reset nibble at position idx_nibbles
		// Set nibble at position idx_nibbles

		unsigned nibble = get_nibble(n, idx_nibbles);
		nibble = rotate_nibble_left(nibble);
		n = reset_nibble(n, idx_nibbles);
		n = set_nibble(n, idx_nibbles, nibble);
	}
	return n;
}

unsigned getMinRotL(unsigned n) {
	unsigned min = n;

	for(int i = 0; i < 4; ++i) {
		n = rotate_nibbles_left(n);
		min = n < min ? n : min;
	}

	return min;
}

void test() {
	printf("Testing get_nibble\n");

	printf("0x%X\n", get_nibble(0x12345678, 0)); // 0x8
	printf("0x%X\n", get_nibble(0x12345678, 1)); // 0x7
	printf("0x%X\n", get_nibble(0x12345678, 2)); // 0x6
	printf("0x%X\n", get_nibble(0x12345678, 3)); // 0x5
	printf("0x%X\n", get_nibble(0x12345678, 4)); // 0x4
	printf("0x%X\n", get_nibble(0x12345678, 5)); // 0x3
	printf("0x%X\n", get_nibble(0x12345678, 6)); // 0x2
	printf("0x%X\n", get_nibble(0x12345678, 7)); // 0x1

	printf("Test rotate_nibble_left\n");

	printf("0x%X\n", rotate_nibble_left(0x9)); // 0x3
	printf("0x%X\n", rotate_nibble_left(0x3)); // 0x6
	printf("0x%X\n", rotate_nibble_left(0x6)); // 0xC
	printf("0x%X\n", rotate_nibble_left(0xC)); // 0x9

	printf("Test reset_nibble\n");

	printf("0x%X\n", reset_nibble(0x12345678, 0)); // 0x12345670
	printf("0x%X\n", reset_nibble(0x12345670, 1)); // 0x12345600
	printf("0x%X\n", reset_nibble(0x12345600, 2)); // 0x12345000
	printf("0x%X\n", reset_nibble(0x12345000, 3)); // 0x12340000
	printf("0x%X\n", reset_nibble(0x12345000, 7)); // 0x2345000

	printf("Test set_nibble\n");

	printf("0x%X\n", set_nibble(0, 0, 0xA)); // 0xA
	printf("0x%X\n", set_nibble(0, 1, 0xB)); // 0xB0
	printf("0x%X\n", set_nibble(0x000000BA, 2, 0xC)); // 0xCBA
	printf("0x%X\n", set_nibble(0x00000CBA, 7, 0x1)); // 0x10000CBA

	printf("Test rotate_nibbles_left\n");

	printf("0x%X\n", rotate_nibbles_left(0x88888888)); // 0x11111111
	printf("0x%X\n", rotate_nibbles_left(0x11111111)); // 0x22222222
	printf("0x%X\n", rotate_nibbles_left(0x22222222)); // 0x44444444
	printf("0x%X\n", rotate_nibbles_left(0x44444444)); // 0x88888888

	printf("Test rot_minima\n");

	printf("0x%X\n", getMinRotL(0x88888888)); //0x11111111
	printf("0x%X\n", getMinRotL(0x44444444)); //0x11111111
	printf("0x%X\n", getMinRotL(0x22222222)); //0x11111111
	printf("0x%X\n", getMinRotL(0x11111111)); //0x11111111
} 

int main() {
	test();
	return 0;
}


