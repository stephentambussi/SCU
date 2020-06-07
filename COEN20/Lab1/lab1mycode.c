#include <stdint.h>
//This function converts the bits to an unsigned integer
uint32_t Bits2Unsigned(int8_t bits[8])
{
	uint32_t n = 0;
	for(int i=7; i>=0; i--)//goes through the array and individually changes each one
		n=(2*n)+bits[i];
	return n;
}
//Converts the bits to a signed integer(can be positive or negative)
int32_t Bits2Signed(int8_t bits[8])
{
	int32_t k = (int32_t)Bits2Unsigned(bits);
	if(k>127)//if greater than 127 subtract 256 to make it negative 
		k=k-256;
	return k;
}
//Increments the bits by 1
void Increment(int8_t bits[8])
{
	int carry = 1;
	for(int i=0; i<=7; i++)//starts at 0 compared to 7 b/c arrays are read left-to-right
	{
		if(carry==1)
		{
			if(bits[i]==0)
			{
				bits[i]=1;
				carry=0;
			}
			else
			{
				bits[i]=0;
				carry=1;
			}
		}
	}
}
//Converts positive number to binary number using repeated division method
void Unsigned2Bits(uint32_t n, int8_t bits[8])
{
	for(int i=0; i<=7; i++)
	{
		bits[i] = n%2;
		n=n/2;
	}
}