#include <stdio.h>
#include <math.h>
/*Write functions that compute the Taylor series for ex, cos, and sin (for a given value of x). 
Stop when the current term becomes smaller than a given value (e.g. 1e-6).*/

unsigned long int factorial(unsigned n){

	if(n<=1)
		return 1;
	return n*factorial(n-1);
}

double taylor(double x,unsigned int n){

	double term=pow(x,n)/factorial(n);
	if(term<1e-6)
		return term;
	return term+taylor(x,n+1);
}

double taylor_wrapper(double x) {
	return taylor(x, 0);
}

int main(){

	printf("Taylor series for x=2 is %lf ", taylor_wrapper(2));
	return 0;
}
