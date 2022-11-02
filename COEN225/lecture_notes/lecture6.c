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
    float f = 1.0 * 3;
    printf("%f\n", f);
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
  - 3 is converted to a float

. ranks: integers in an operation will be promoted to the largest int type present according to the below hierarchy
  rank(long long) > rank(int) > rank(short) > rank(char)

. promotion 
  example: int i=2147483647; long long l = i+1LL;

. truncation 
  example: short s; int i=0x10000; s = i;

. cast 
  example: int i=2147483647; long long l = (long long)i+1;

. unsigned to signed 
  bit patterns preserved value --> (2^31)-1 becomes negative

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
*   - Signed truncation from long --> short --> char makes values negative from the left
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
*     overwritten by going outside the array bounds of itemlist[0-4]. By passing the program "5 0", 
*     the balance can be changed to be 0.
*
*   Format String Vulnerabilities
*   -----------------------------------------
*   printf() call on the stack
*   - In memory, as seen in gdb, format specifier address is replaced with values for format specifier 
*     which are immediately after the format specifier address in memory.
*   - When one of the values for 2 format specifiers is missing in the printf statement, the 2nd
*     specifier value is still retrieved from the next memory word on the stack. This leads to 
*     the printf statement displaying a value or address from the runtime stack --> VULNERABILITY
*   - This vulnerability can be expanded to print the entire runtime stack.
*   
*   Displaying stack data with printf format strings
*   - Using printf vulnerability, Duo Factor Authentication app using gets(choice) and then 
*     printf(choice) if user entered wrong choice can be exploited. printf(choice) treats choice
*     like a format specifier so user can pass in "%x,%x,..." to print runtime stack values.
*     - Printing stack values --> hacker can find return address for function to perform code/arc injection
*   
*   Arbitary writing to memory with %n format specifier
*   - %n format specifier loads into variable pointed by corresponding argument. The loading is done with a value
*     which is equal to the number of characters printed by printf() before the occurrence of %n.
*     - %n does not print anything.
*   Ex: 
*     printf("The value of %ns : ", &s);
*     printf("%d", s);
*   Output: The value of s : 13 --> 13 is the num of characters before the occurrence of %n
*   - See video for exploit that combines %n and printf vulnerability
*   
*   Duo Factor Authentication App Exploit
*   - Using the above exploit to write to memory with %n specifier, duo authentication app can
*     be exploited to authenticate without actually authenticating on app.
*   
*   Using printf to overwrite GOT entry
*   - printf has limitations on how much it can write to memory with %n specifier
*     - Using divide and conquer, portions of the destination address can be written
*       at a time rather than all at once
*/