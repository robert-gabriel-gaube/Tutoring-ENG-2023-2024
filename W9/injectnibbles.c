#include<stdio.h>
#include<stdint.h>

uint64_t getNibble(uint32_t n, unsigned int k)
{
	return ((n >> (k*4)) & 0xF);
}




uint64_t set(uint64_t b,uint64_t nibble, unsigned pos)
{
	return b | nibble<< pos;
}





uint64_t injectNibbles(uint32_t n)
{
	uint64_t result=0;
	int k=0;

	for(int i=0;i< 8;i++)
	{
		result= set(result,getNibble(n, i),k);
		k=k+8;
	}

	k=4;
	uint64_t valueXOR;

	for(int i=0;i<8;i++)
	{
		if(i==7)
		{
			valueXOR= getNibble(n,i)^getNibble(n,0);
		}
		else
		{
			valueXOR=getNibble(n,i)^ getNibble(n,i+1);
		}
		result= set(result,valueXOR,k);
		k=k+8;
	}


	return result;

}

int main()
{
	printf("%lx\n", injectNibbles(0x12345678) );
}