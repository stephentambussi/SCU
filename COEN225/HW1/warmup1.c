/*  
*   Stephen Tambussi
*   COEN225
*   HW1: warmup 1
*   10/4/22
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void endianness(void arg)
{
    int test_val = 0x10000002;
    char *ptr = (char *) &test_val; //points to value at starting memory address
    printf("%x \n", *ptr);
    if(*ptr == 0x2)
    {
        /*
        *   Little endian: least significant byte of word is stored at smallest mem address
        *   Architectures: x86
        *   Example: test_val will be stored in mem as: start_addr-> [ 2 0 0 0 0 0 0 1 ] <-end_addr
        */
        printf("This system is little endian. \n");
        return;
    }
    else if(*ptr == 0x1)
    {
        /*
        *   Big endian: most significant byte of word is stored at smallest mem address
        *   Architectures: ARM(kinda)
        *   Example: test_val will be stored in mem as: start_addr-> [ 1 0 0 0 0 0 0 2 ] <-end_addr
        */
        printf("This system is big endian. \n");
        return;
    }
    else
    {
        printf("We were so concerned about whether we could do it... ");
        printf("that we didn't stop to think if we should do it. \n");
        return;
    }
}

int main(void)
{
    endianness();
    return 0;
}