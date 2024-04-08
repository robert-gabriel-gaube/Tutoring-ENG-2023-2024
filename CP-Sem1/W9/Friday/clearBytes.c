#include <stdio.h>
#include <stdint.h>
/*
"Given two 32-bit numbers, a and b, the objective is to identify bytes at positions 0, 8, 16, and 24 within a 
that are present in any of the corresponding positions in b, replace the identified byte in b with the byte 0x00."

For example:
A = 0x 12 34 56 78
B = 0x AB 34 12 C5

After reseting of bytes b becomes 0x AB 00 00 C5

*/

uint32_t getByte(uint32_t n, unsigned k)
{
    return (( n >> ( k * 8 ) ) & 0xFF); 
}

uint32_t clearByte(uint32_t n, unsigned k)
{
    return ( n & ~( 0xFF << ( k * 8 ))); 
}

uint32_t SetOnZeroBytes(uint32_t A, uint32_t B)
{
    uint32_t byteOfA;
    uint32_t byteOfB;
    // sizeof(val) gives the size in BYTES 
    for( int i=0; i<sizeof(A) ; i++ )  // go through all the bytes of A
    {
        byteOfA = getByte(A,i);
        for( int j=0 ; j<sizeof(B) ; j++ ) // go through all the bytes of B
        {
            byteOfB = getByte(B,j);
            if((byteOfA ^ byteOfB) == 0) // <==> if(byteOfA == byteOfB) but it's nicer to use bitwise operators, not logical :)
            {
                B=clearByte(B,j);
            }
        }
    }
    return B;
}

int main()
{
	uint32_t A= 0x12345678;
	uint32_t B= 0xAB3412C5;
	printf("B = 0x %x", SetOnZeroBytes(A,B));
	return 0;
}