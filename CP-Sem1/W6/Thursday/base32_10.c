#include <stdio.h>
#include <ctype.h>
int is32bdigit(char c) {
	return (c >= '0' && c <= '9') || (toupper(c) >= 'A' && toupper(c) <= 'V'); 
}
int base32_symbol_to_base10(char c) {
	if(isdigit(c)) {
		return c - '0';
	}
	else if(is32bdigit(c)) {
		return toupper(c) - 'A' + 10;
	} 
	return -1;
}	
char base10_symbol_to_base32(int digit) {
	if(digit < 10 && digit >= 0) {
		return '0' + digit;
	}
	else if(digit < 32) {
		return 'A' + digit - 10;
	}
	return 0;
}
void test() {
	printf("Testing is32bdigit\n");
	printf("%s\n", is32bdigit('V') ? "true" : "false"); // true
	printf("%s\n", is32bdigit('A') ? "true" : "false"); // true
	printf("%s\n", is32bdigit('f') ? "true" : "false"); // true
	printf("%s\n", is32bdigit('0') ? "true" : "false"); // true
	printf("%s\n", is32bdigit('V') ? "true" : "false"); // true
	printf("%s\n", is32bdigit('8') ? "true" : "false"); // true 
	printf("%s\n", is32bdigit('X') ? "true" : "false"); // false 
	printf("%s\n", is32bdigit('z') ? "true" : "false"); // false

	printf("Testing base32 to base 10\n");
	printf("%d\n", base32_symbol_to_base10('0')); // 0
	printf("%d\n", base32_symbol_to_base10('6')); // 6
	printf("%d\n", base32_symbol_to_base10('9')); // 9
	printf("%d\n", base32_symbol_to_base10('A')); // 10
	printf("%d\n", base32_symbol_to_base10('a')); // 10
	printf("%d\n", base32_symbol_to_base10('F')); // 15
	printf("%d\n", base32_symbol_to_base10('V')); // 31
	printf("%d\n", base32_symbol_to_base10('v')); // 31
	printf("%d\n", base32_symbol_to_base10('x')); // -1

	printf("Testing base10 to base32\n");
	printf("%c\n", base10_symbol_to_base32(0)); // 0
	printf("%c\n", base10_symbol_to_base32(9)); // 9
	printf("%c\n", base10_symbol_to_base32(10)); // A
	printf("%c\n", base10_symbol_to_base32(15)); // F
	printf("%c\n", base10_symbol_to_base32(31)); // V
	printf("%c\n", base10_symbol_to_base32(34)); // character 0 which is NULL
}
int main() {
	test();
	return 0;
}
