#include <stdio.h>
#include <ctype.h>

typedef enum{
    start, // 0
    word, // 1
    digit, // 2
    floater, // 3
    other // 4
} states;

void printRow()
{
    int ch;
    //unsigned int state=0;
    states state; 
    unsigned int wordCount = 0;
    unsigned int integerCount = 0;
    unsigned int floatCount = 0;
    unsigned int otherCount = 0;
    
    unsigned int isfloat=0;
    while((ch = getchar()) != EOF) {
        if(isalpha(ch) && ((state == start) || (state == word))) 
            state = word; 

        else if(isdigit(ch) && ((state == start) || (state == digit))) 
            state = digit;

        else if(((state == digit) || (state == floater)) && ((ch == '.') || (isdigit(ch))) ) {
            if(ch == '.') 
                isfloat++;

            if(isfloat == 1)
                state = floater;

            else 
            	state = other;
        }

        else if( !isspace(ch) )
            state = other;

        else if( isspace(ch) ) {
            if(state == 1) wordCount++;
            else if(state == 2) integerCount++;
            else if(state == 3)	floatCount++;
            else if(state == 4)	otherCount++;
            isfloat = 0;
            state = 0;
        }
        if(ch == '\n') {
            printf("\n Word count:%d \n",wordCount);
            printf("Int count:%d \n",integerCount);
            printf("Float count:%d \n",floatCount);
            printf("Other count:%d \n",otherCount);
            wordCount = 0;
            integerCount = 0;
            floatCount = 0;
            otherCount = 0;
        }
    }

    if(state == 1) wordCount++;
    else if(state == 2) integerCount++;
    else if(state == 3)floatCount++;
    else if(state == 4)otherCount++;

    printf("\n Word count:%d \n",wordCount);
    printf("Int count:%d \n",integerCount);
    printf("Float count:%d \n",floatCount);
    printf("Other count:%d \n",otherCount);
}

int main() {
    printRow();
    return 0;
}