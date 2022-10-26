#include <stdio.h>
#include <string.h>
void copy(char *dst, char *src, unsigned int len)
{
    printf("len=%u\n",len);
    while (len--) {
        *dst++ = *src++;
    }
}
int main()
{
    char dest[64];
    copy(dest,"abc",3);   // expected
    copy(dest,"abc",-1);  // unexpected: -1 becomes a large unsigned
    return 0;
}