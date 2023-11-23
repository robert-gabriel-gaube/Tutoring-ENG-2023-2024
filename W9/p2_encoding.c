#include <stdio.h>
#include <stdint.h>

uint32_t set_bit(uint32_t set, int pos) {
	return (set | (1 << pos));
}

int char_to_int(char c) {
	return c - 'a';
}

uint32_t create_set(char s[]) {
	uint32_t set = 0;
	int idx = 0;
	while(s[idx] != '\0') {
		int char_value = char_to_int(s[idx]);
		set = set_bit(set, char_value);
		++idx;
	}
	return set;
}

uint32_t extract_bit(uint32_t set, int pos) {
	return (set & (1 << pos));
}

char int_to_char(int val) {
	return 'a' + val;
}

void print_chars(uint32_t set) {
	for(int idx = 0; idx <= 'z' - 'a'; ++idx) {
		if(extract_bit(set, idx)) {
			printf("%c ", int_to_char(idx));
		}
	}
	printf("\n");
}

void test() {
	printf("Testing create_set\n");

	char s[] = "abcd\0";
	uint32_t set = create_set(s);
	printf("0x%X\n", set); //0xF

	print_chars(set); // a b c d
}

int main() {
	test();
	return 0;
}