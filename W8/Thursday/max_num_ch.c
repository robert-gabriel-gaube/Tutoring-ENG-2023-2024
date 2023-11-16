#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
/*Implement a function which reads data from input,
until end-of-line (’\n’), and prints the maximum of the
integer values found in the input. A number is a set of up to 9 digits,
separated by at least one space character, excepting the
first or last position where there could be missing the leading or trailing space. */

void get_max_num(){
	char ch;
	int x = 0;
	int max = 0;
	int got_space = 1;

	while((ch = getchar()) != EOF){
		if(isdigit(ch) && got_space == 1){
			x = x * 10 + (ch - '0');
		}
		else if(ch == ' '){
			got_space = 1;
			if(max < x)
				max = x;
			x = 0;
		}
		else if (ch == '\n'){
			if(max < x)
				max = x;
			x = 0;
			printf("max = %d\n", max);
			max = 0;
		}
		else{
			got_space = 0;
			x = 0;
		}
	}
}

int main(int argc, char const *argv[]){
	get_max_num();

	return 0;
}