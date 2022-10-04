/*  
*   Stephen Tambussi
*   COEN225
*   HW1: problem 3
*   10/4/22
*/
#include <string>
#include <stdio.h>
#include <string.h>
int main()
{
    std::string s1 = "abc";
    std::string s2 = "";
    char *cp1 = (char*) s1.c_str();
    char *cp2 = (char*) s2.c_str();
    printf("&s1=%p\n",cp1); //addr = 0xbffff684 = 3,221,223,044
    printf("s1=%s\n",cp1);
    printf("&s2=%p\n",cp2); //addr = 0xbffff69c = 3,221,223,068
    printf("s2=%s\n",cp2);
    scanf("%s",cp1);
    printf("s1=%s\n",cp1);
    printf("s2=%s\n",cp2);
}
/*  Solution:
*   Difference in addr between s1 & s2 is 24 bytes. When overwritting s2,
*   the first 16 chars (bytes) to s1 can be any value. However, the next 4 bytes
*   should be the memory address for s2 (printed from printnop.c) as greater than 16 bytes
*   will begin to overwrite the address of s2. This is to prevent the seg fault that results 
*   from the C++ string mem deallocator attempting to free the memory at the overwritten and 
*   therefore invalid address. The 4 bytes after the mem address can be anything (I chose '0000').
*   Finally, the input line should end with 123.
*   
*   Input:
*   0123456789abcdefXXXX0000123 --> X = mem addr from printnop
*/

/*  Scratch work
*   s1 mem addr: 0xbffff67c
*   cp1 mem addr: 0xbffff684
*   s2 mem addr: 0xbffff694
*   cp2 mem addr: 0xbffff69c
*/