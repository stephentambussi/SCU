#include <stdio.h>

int main(void) {
    signed int l;   /* 32-bit datatype */
    signed short s; /* 16-bit datatype */
    signed char c;  /* 8-bit datatype */

    l = 0xcafebabe;
    s = l;
    c = l;

    printf("l = 0x%x %d (%ld bits)\n", l, l, sizeof(l) * 8);
    printf("s = 0x%x %d (%ld bits)\n", s, s, sizeof(s) * 8);
    printf("c = 0x%x %d (%ld bits)\n", c, c, sizeof(c) * 8);

    return 0;
}
