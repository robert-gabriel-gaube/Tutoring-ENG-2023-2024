#include <stdio.h>
#include <math.h>
/*
Write a function that decomposes a number into prime factors and prints out the result, 
in the form: 18=2*3^2. Try both a recursive and an iterative solution.
Warning, ^ does *not* denote exponentiation in C.
*/

int check(int num, int index){
	int pow = 0;
	while(num % index == 0){
		pow ++;
		num = num / index;
	}

	if(pow != 0){
		printf("%d^%d*", index, pow);
	}

	return num;

}

void prime_fact(int num){
	num = check(num, 2);

	for(int i = 3; i <= num && num != 1; i = i + 2)f
		num = check(num, i);
}

int main(){
	int num = 9999;
	prime_fact(num);
	return 0;
}
