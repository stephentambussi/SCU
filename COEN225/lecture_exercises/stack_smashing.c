/* Lecture 2 - Stack smashing exploit
*  - Need to compile with -fno-stack-protector
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IsPasswordOK(void)
{
    char Password[12];
    (void) gets(Password);
    return 0 == strcmp(Password, "goodpass");
    /*
    *   You can modify this function's return address
    *   on the stack to change where it returns. This
    *   will redirect the program in any way you like.
    *   This return address modification is the basis
    *   for code injection and enabling a shell.
    */
}

int main(void)
{
    int PwStatus;
    puts("Enter Password: ");
    PwStatus = IsPasswordOK();
    if(!PwStatus)
    {
        puts("Access denied");
        exit(-1);
    }
    else
        puts("Access granted");
}