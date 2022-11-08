/*
*   Code to perform Duo Factor Authentication App exploit from lecture 7
*   NOTE: this program must be executed on the VM for the exploit to work
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int choiceok = 0;
char password[16];
char passcode[16];

void duo_factor()
{
    char choice[16];
    choiceok = 0;
    do {
        puts("Enter a passcode or select one of the following options:\n");
        puts("1. Duo Push to XXX-XXX-6455");
        puts("2. Phone call to XXX-XXX-6455");
        puts("3. SMS passcodes to XXX-XXX-6455 (next code starts with: 2)");

        gets(choice);
        if(choice[0] < '1' || choice[0] > '3')
        {
            printf("bad choice:");
            printf(choice);
            printf("\n");
        }
        else
        {
            puts("enter passcode:");
            gets(passcode);
            if(strcmp(passcode, "goodcode") == 0)
                choiceok = 1;
        }
    } while (!choiceok);
    puts("success!");
}

int main(void)
{
    puts("Enter Password:");
    gets(password);
    if(strcmp(password, "goodpass") == 0)
    {
        puts("Password accepted, now duo factor authentication");
        duo_factor();
    }
    return 0;
}

/*
*   How to do the exploit on this program:
*   
*   1) Get address of choiceok variable:
*       Command: objdump -t <executable_name> | grep choiceok
*       Output:  <choiceok_address> g     O .bss   0000000000000004              choiceok
*   2) Figure out the distance of the format string from the top of the stack:
*       Input to duo app: %x, %x, %x, %x
*       Output:           bad choice:<1st_word_addr>,<2nd_word_addr>,<3rd_word_addr>,<format_string>
*       So the distance is 3 words from the top of the stack
*   3) Create the payload
*       - Use the address of the choiceok variable in the printnop program and redirect its output to a file
*         to create the payload file
*       - Add the string "goodpass" at the beginning of the newly created payload file
*   4) Run the duo app program with the payload file as input
*       NOTE: this does not work on WSL terminal
*/