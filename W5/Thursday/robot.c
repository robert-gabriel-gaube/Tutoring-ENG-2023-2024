/*
Create a software solution for a robot that takes instructions as 
input and moves based on these instructions. 

An instruction is composed of 2 hexadecimal letters, the first 2 bits of the first character 
dictate the direction in which the robot will go, the other 6 bits will represent the number 
of spaces the robot will move in that direction. 

Your job is to decrypt these instructions and to print out the positions of the robot in a 
xoy axis system in the form x, y. The robot starts from the position 0(x), 0(y).

The input stream of instructions stops when the instruction 00 is encountered.
We are sure that the input is correct, it adheres strictly to the formulated statement.

*/


#include <stdio.h>
#include <ctype.h>

int x = 0, y = 0;

int hex_to_dec(char ch) {
	if(isdigit(ch)) {
		return ch - '0';
	}
	if(isxdigit(ch)) {
		return toupper(ch) - 'A' + 10;
	}
	return -1;
}

int extract_direction(int number) {
	return (number >> 2) & 0b11;
}

int extract_number_of_spaces(int number1, int number2) {
	return (number2 | ((number1 & 0b11) << 4));
}
void make_move(int direction, int numberOfSpaces) {
	switch(direction) {
		case 0: y += numberOfSpaces; break;
		case 1: x -= numberOfSpaces; break;
		case 2: y -= numberOfSpaces; break;
		case 3: x += numberOfSpaces; break;
	}
}
void process_instruction(char ch1, char ch2) {
	int hexCh1 = hex_to_dec(ch1), hexCh2 = hex_to_dec(ch2);
	int direction = extract_direction(hexCh1);
	int numberOfSpaces = extract_number_of_spaces(hexCh1, hexCh2);
	make_move(direction, numberOfSpaces);
	printf("%d, %d\n", x, y);
}

void process_input() {
	char ch1 = getchar(), ch2 = getchar();
	while(ch1 != '0' || ch2 != '0') {
		process_instruction(ch1, ch2);
		ch1 = getchar(); 
		ch2 = getchar();
	}
}

void test() {
	printf("Test hex_to_de\n");

	printf("%d\n", hex_to_dec('a')); // 10
	printf("%d\n", hex_to_dec('9')); // 9
	printf("%d\n", hex_to_dec('1')); // 1
	printf("%d\n", hex_to_dec('B')); // 11
	printf("%d\n", hex_to_dec('F')); // 15
	printf("%d\n", hex_to_dec('X')); // -1

	printf("Test extract_direction\n");

	printf("%d\n", extract_direction(0x0)); // 0
	printf("%d\n", extract_direction(0x4)); // 1
	printf("%d\n", extract_direction(0x8)); // 2
	printf("%d\n", extract_direction(0xC)); // 3

	printf("Test extract_number_of_spaces\n");

	printf("%d\n", extract_number_of_spaces(0x0,0x1)); // 1
	printf("%d\n", extract_number_of_spaces(0x0,0xF)); // 15
	printf("%d\n", extract_number_of_spaces(0x1,0x0)); // 16
	printf("%d\n", extract_number_of_spaces(0x1,0x3)); // 19
	printf("%d\n", extract_number_of_spaces(0x9,0xC)); // 28

	printf("Test move\n");

	printf("%d, %d\n", x, y); // 0, 0
	make_move(0, 5);
	printf("%d, %d\n", x, y); // 0, 5
	make_move(3, 10);
	printf("%d, %d\n", x, y); // 10, 5
}

int main() {
	process_input();
	return 0;
}
