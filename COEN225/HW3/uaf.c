/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 1
*   11/1/22
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct customer
{
    char name[16];
    char creditcard[16];
};
int main()
{
    struct customer *cptr;
    char cmd[16];
    do
    {
        puts("1. enter credit card info");
        puts("2. buy parking ticket");
        puts("3. done");
        gets(cmd);
        if (strcmp(cmd, "1") == 0)
        {
            cptr = (struct customer *)calloc(1, sizeof(struct customer));
            puts("enter name:");
            gets(cptr->name);
            puts("enter credit card:");
            gets(cptr->creditcard);
        }
        else if (strcmp(cmd, "2") == 0)
        {
            printf("charged $10 to credit card:%s\n", cptr->creditcard);
        }
        else if (strcmp(cmd, "3") == 0)
        {
            puts("buy session done!");
            if (cptr)
                free(cptr);
            puts("New session...");
        }
    } while (1);
}