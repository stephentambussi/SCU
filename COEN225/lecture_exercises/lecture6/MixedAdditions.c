#include <stdio.h>
#include <string.h>
int main()
{
    unsigned int a = 6;
    int b = -20;

    if ((a + b) > 6)
        puts(">6");
    else
        puts("<=6");
}