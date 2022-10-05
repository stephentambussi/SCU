/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 2
*   9/27/22
*/
#include <stdio.h>
#include <string.h>

int main(void)
{
    return 0;
}

/*
*   Static code analyzer: flawfinder
*   Dynamic code analyzer: valgrind --> can detect memory leaks
*
*   Process Memory Organization
*   - Stack typically grows down
*   
*   Stack-based exploit: Stack Smashing
*   - Can overwrite function's return address in stack --> effectively redirecting to any code you want
*       - Can also use this to modify variables
*   
*   Code-injection
*   - Adding code after victim code in stack & then change return address to point to injected code
*       - Injected code needs to be compiled into object code first
*/