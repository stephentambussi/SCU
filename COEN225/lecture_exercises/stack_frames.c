/* Lecture 2 - Stack frames explained
*  - Need to compile with -fno-stack-protector
*/
#include <stdio.h>
#include <stdlib.h>

void foo(int i, char *name)
{
    char LocalChar[24];
    int LocalInt;
    LocalInt = i;
    return;
}

int main()
{
    int MyInt = 1;
    char *MyStrPtr = "MyString";
    foo(MyInt, MyStrPtr);
    return 0;
}