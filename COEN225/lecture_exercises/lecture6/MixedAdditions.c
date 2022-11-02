#include <stdio.h>
#include <string.h>
int main()
{
    unsigned int a = 6;
    int b = -20;

    if ((a + b) > 6) //result of unsigned + signed = unsigned result (b converted to unsigned)-->types converted from left to right
        puts(">6");
    else
        puts("<=6");
}