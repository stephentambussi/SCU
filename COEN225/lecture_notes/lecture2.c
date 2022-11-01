/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 2
*   9/27/22
*/
#include <stdio.h>
#include <stdlib.>
#include <string.h>

int gi; //ON BSS SEGMENT
int gj = 1; //ON DATA SEGMENT
static int si; //ON BSS SEGMENT
static int si2 = 2; //ON DATA SEGMENT
int a1[4] = {0,1,2,3}; //ON DATA SEGMENT
static int sa1[4] = {0,1,2,3}; //ON DATA SEGMENT
int a10[1000]; //ON BSS SEGMENT

int main(void) //function and its parameters = STACK
{
    int x = 1; //ON STACK
    static int msx; //ON BSS SEGMENT
    static int msy = 1; //ON DATA SEGMENT
    char *cp = (char *) malloc(10); //ON HEAP (address is lower than cp2)
    char *cp2 = (char *) malloc(10); //ON HEAP (address is higher than cp)
    return 0;
}

/*
*   Static code analyzer: flawfinder
*   Dynamic code analyzer: valgrind --> can detect memory leaks
*
*   Process Memory Organization
*   |          Text         |   Start of mem (lower address)
*   |          Data         |
*   |          BSS          |
*   |          Heap         |   Heap grows 'upward' (lower --> higher address)
*   |           |           |
*               V
*   |           ^           |
*   |           |           |   Stack grows 'downward' (higher --> lower address)
*   |          Stack        |   End of mem (higher address)
*
*   
*   Stack-based exploit: Stack Smashing
*   - Can overwrite function's return address in stack --> effectively redirecting to any code you want
*       - Can also use this to modify variables
*
*   Arc Injection   
*   - Modifies execution flow of running program by redirecting the currently running program
*     to another function/method currently in its memory space.
*     Ex:
*       [12 bytes for Password[12]] [12 bytes for padding   ] [return address]...
*                                                                |            
*        main function line 20 <----------------------------------
*   
*   Code Injection
*   - Adding code after victim code in stack & then change return address to point to injected code
*       - Injected code needs to be compiled into object code first and stack needs to be executable
*     Ex:
*       [12 bytes for Password[12]] [12 bytes for padding   ] [return address] [injected object code]...
*                                                               |                ^
*                                                               |                |
*                                                               ------------------   
*
*   Misc.
*   - '-fno-stack-protector' arg will remove the stack canary that prevents stack exploits
*   
*/