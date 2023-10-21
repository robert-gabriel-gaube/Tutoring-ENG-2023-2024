/* 

Write a program that properly indents a text read from standard input that has balanced braces { } . The output is formed as follows:

 -- Any brace must be followed by a newline.

 -- Any closing brace } is on a line by itself.

 -- Any non-empty line between n levels of braces starts with 2*n spaces. After these spaces, a non-whitespace character must follow.

 -- No other changes are done to the text.

 */

#include <stdio.h>
#include <ctype.h>

void print_spaces(int n) {
	while(n--) {
		printf("  ");
	}
}

void process_c_text() {
	char ch;
	int open_braces = 0, is_last_char_newline = 0;
	while((ch = getchar()) != EOF) {
		if(ch == '\n') {
			is_last_char_newline = 1;
			putchar(ch);
		}
		else if(ch == '{') {
			printf("{\n");
			++open_braces;
			is_last_char_newline = 1;
		} 
		else if(ch == '}') {
			--open_braces;
			if(!is_last_char_newline) {
				// Prevents case when }} would be printed on 3 lines instead of 2
				putchar('\n');
			}
			print_spaces(open_braces); 
			printf("}\n");
			is_last_char_newline = 1;
		} 
		else {
			if(is_last_char_newline) {
				print_spaces(open_braces);
				is_last_char_newline = 0;
			}
			putchar(ch);
		}
	}
}

int main() {
	process_c_text();
	return 0;
}