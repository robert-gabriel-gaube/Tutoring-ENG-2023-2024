#include <stdio.h>

unsigned extract_nibble(unsigned num, unsigned pos) {
	return ((num >> (4 * pos)) & 0xF);
}

int nondecreasing_nibbles(unsigned n) {
	unsigned old_nibble = extract_nibble(n, 0);
	unsigned current_nibble = 0;

	for(int idx = 1; idx < sizeof(n) * 2; ++idx) {
		current_nibble = extract_nibble(n, idx);

		if(old_nibble < current_nibble) {
			return 0;
		}

		old_nibble = current_nibble;
	}
	return 1;
}

void test() {
	printf("Testing nondecreasing_nibbles\n");

	printf("%d\n", nondecreasing_nibbles(0x6AD)); // 1
	printf("%d\n", nondecreasing_nibbles(0xAD6)); // 0
}
int main() {
	test();
	return 0;
}