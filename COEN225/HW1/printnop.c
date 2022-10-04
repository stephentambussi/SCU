/* Utility program for problem 3 */
#include <stdio.h>
int main()
{
    unsigned int nonprintable=0xbffff6ac;
    printf("%s\n",(char *)&nonprintable);
    return 0;
}