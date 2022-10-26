/* width1.c - exploiting a trivial widthness bug */
#include <stdio.h>
#include <string.h>
int cmp(unsigned short a, unsigned short b)
{
    printf("a=%u\n", a);
    if (a >= b)
        return 1;
    else
        return 0;
}
int main(int argc, char *argv[])
{
    int i;
    char buf[80];

    if (argc < 3)
    {
        return -1;
    }
    i = atoi(argv[1]);

    if (cmp(i, 80))
    {
        printf("Request exceeding 80 bytes, exiting!\n");
        return -1;
    }
    memcpy(buf, argv[2], i);
    buf[i] = '\0';
    printf("%s\n", buf);
    return 0;
}
