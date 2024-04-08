#include <stdio.h>
#include <ctype.h>

/*
Write a program that reads all input and prints, for each paragraph, the number of words and lines. 
A paragraph is a portion of text that does not start with a newline, 
ends with a single newline or EOF and is separated by at least one newline from other paragraphs.
*/

int parag_count = 0;

void process_parag(){
	int line_count = 0, word_count = 0;
	int end_paragraph = 0, is_last_char_space = 0;
	char ch;

	while(!end_paragraph) {
		ch = getchar();
		if(ch == ' ') {
			// We don't want to count space as a word 
			// (case of multiple consecutive spaces)
		    if(is_last_char_space == 0) {
		        ++word_count;
		    }
			is_last_char_space = 1;
		} 
		else if(ch == '\n') {
			char ch_1 = getchar();

			// End line and word (not counting any trailing spaces)
			if(is_last_char_space==0) {
		        ++word_count;
		    }
			++line_count;
			is_last_char_space = 0;

			// End paragraph
			if(ch_1 == '\n') {
				end_paragraph = 1;
			
			}
		} 
		else {
			// End paragraph
			if(ch == EOF) {
				end_paragraph = 1;
			}
			is_last_char_space = 0;
		}
	}
	printf("Paragraph #%d has %d words and %d lines\n", parag_count, word_count, line_count);
}

void process_text(){
	char ch;
	while((ch = getchar()) != EOF){
		// Found paragaraph
		if(isalnum(ch)){  
			++parag_count;
			process_parag();
		}
	}
}

int main(){
	process_text();
	return 0;
}