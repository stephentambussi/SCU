/*  
*   Stephen Tambussi
*   COEN225
*   HW2: problem 2 -- TODO: finish
*   10/18/22
*/
#include <stdio.h>
int main()
{
    unsigned int nonprintable=0xbffff6ac;
    printf("%s\n",(char *)&nonprintable);
    return 0;
}

/*  Desired output:
*   To view employee info, please enter your name:
*   john, 500000+100,000 bonus will be deposited to the account
*   peter, 150000+10,000 bonus will be deposited to the account
*   adam, 50000+100,000 bonus will be deposited to the account
*   Title:President john
*   Title:Director peter
*   Title:Janitor adam
*
*   Exploit should enable the Janitor object to invoke President's pay function, but keep Janitor's info function the same
*/