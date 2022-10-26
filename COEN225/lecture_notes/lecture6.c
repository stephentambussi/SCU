/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 6
*   10/25/22
*/
#include <stdio.h>
#include <string.h>

int main(void)
{
    return 0;
}

/*
*   Integer Vulnerabilities
*   -----------------------------------------
*   Integer Representation - 2s complement
             binary:
unsigned: 0: 00000000000000000000000000000000
          1: 00000000000000000000000000000001
          2: 00000000000000000000000000000010
             ...
 4294967294: 11111111111111111111111111111110
 4294967295: 11111111111111111111111111111111

  signed: 0: 00000000000000000000000000000000
          1: 00000000000000000000000000000001
          2: 00000000000000000000000000000010
             ...
 2147483647: 01111111111111111111111111111111
-2147483648: 10000000000000000000000000000000
-2147483647: 10000000000000000000000000000001
-2147483646: 10000000000000000000000000000010
             ...
         -4: 11111111111111111111111111111100
         -3: 11111111111111111111111111111101
         -2: 11111111111111111111111111111110
         -1: 11111111111111111111111111111111
*
*   Integer Types
                                 range:
. signed char (8 bits)           -128.....0.....127
. unsigned char (8 bits)         0.....255
. signed short int (16 bits)     -32768.....0.....32767
. unsigned short int (16 bits)   0.....65535
. signed int (32 bits)           -2147483648.....0.....2147483647
. unsigned int (32 bits)         0.....4294967295 
. long int (32 bits on Ubuntu16)
. long long int (64 bits)        -2^63.....0.....-2^63-1
*
*   Conversion
. assignment, passing parameters
  example: int x=1; short y=2; y=x;

. mixed operands operations
  example: float f = 1.0 * 3;

. ranks: 
  rank(long long) > rank(int) > rank(short) > rank(char)

. promotion 
  example: int i=2147483657; long long l = i+1LL;

. truncation 
  example: short s; int i=0x10000; s = i;

. cast 
  example: int i=2147483657; long long l = (long long)i+1;

. unsigned to signed 
  bit patterns preserved value > 2^31-1 becomes negative

. signed to unsigned: 
  bit patterns preserved. negative signed become large positive
*
*   Truncation Errors
*   DemoTruncate.c outputs:
*       Unsigned                    Signed
*   l = 0xcafebabe (32 bits)    l = 0xcafebabe (32 bits)
*   s = 0xbabe (16 bits)        s = 0xffffbabe (16 bits)
*   c = 0xbe (8 bits)           c = 0xffffffbe (8 bits)
*   - Unsigned truncation from long --> short --> char cuts off values from the left
*   - Signed truncation from long --> short --> char makes values more negative from the left
*   TruncateError1.c output:
*   cresult=-66
*   - c1 + c2 = 190 --> this is the unsigned value, but -66 is the signed value.
*   - This is because the char type is signed (-128 to 127) and so 190 overflows
*   TruncateError2.c output:
*   - Because arguments to cmp function are unsigned short, they can be overflowed and the program
*     will bypass the cmp check to copy memory --> causes a seg fault
*   
*   Signed to Unsigned Error - bypassing sign check
*   - Passing -1 to copy function which expects unsigned length, will convert it to a 
*     large positive value --> causes seg fault
*   
*   Addition Overflow
*   MixedAdditions output:
*   - 6+(-20) = -14 should be less than 6. However, the program outputs ">6"
*   - This is because the signed int b is converted to unsigned before performing addition
*     and since it is negative it becomes very large positive number.
*   - Solution: need to convert unsigned int a to signed int to have program function correctly
*   
*   Integer to Floats Errors
*   - int2float0.c truncates float value since it was assigned to int variable
*   - int2float.c gives very large value because float is attempting to be formatted
*     by integer
*
*   Multiplication Overflow Exploit
*   - Can pass the program a count value for an item that overflows the balance variable
*     because the balance value = count * item price. Ex: 3 1000000000
*
*   Array Bound Index Overflow
*   - Using gdb and looking at the mem layout, it can be seen that the balance variable can be
*     manipulated by going outside the array bounds of itemlist[0-4]. By passing the program "5 0", 
*     the balance can be changed to be 0.
*
*   Format String Vulnerabilities
*   -----------------------------------------
*   printf() call on the stack
*   - TODO: go over
*   
*   Displaying stack data with printf format strings
*   - TODO: go over
*   
*   Arbitary writing to memory with %n format specifier
*   - TODO: go over
*   
*   Duo Factor Authentication App Exploit
*   - TODO: go over
*   
*   Using printf to overwrite GOT entry
*   - TODO: go over
*/