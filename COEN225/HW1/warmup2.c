/*  
*   Stephen Tambussi
*   COEN225
*   HW1: warmup 2
*   10/4/22
*/
#include <stdio.h>
#include <string.h>
int foo(int *main_var)
{
    int foo_var;
    printf("&foo_var = %p\n", &foo_var);
    if(main_var < &foo_var)
        printf("Stack grows upward.\n");
    else if(main_var >= &foo_var)
        printf("Stack grows downward.\n");
    return 0;
}

int main(void)
{
    int main_var;
    printf("&main_var = %p\n", &main_var);
    foo(&main_var);
    return 0;
}
/*
*   Stack growing upward: foo() frame address is higher than main()
*   Stack growing downward: foo() frame address is lower than main()
*/