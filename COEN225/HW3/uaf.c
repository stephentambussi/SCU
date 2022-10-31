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
            if(cptr != NULL) //Added this to prevent invalid access to NULL value
                printf("charged $10 to credit card:%s\n", cptr->creditcard);
        }
        else if (strcmp(cmd, "3") == 0)
        {
            puts("buy session done!");
            if (cptr)
            {
                free(cptr);
                cptr = NULL; //Solution to use-after-free and multiple-free
            }
            puts("New session...");
        }
    } while (1);
}

/*
*   Solutions
*
*   Use-after-free error:
*   If some user enters their name and credit card info and then enters 3 for "done",
*   another user can immediately after use their credit card info for themself by skipping
*   entering their credit card and entering 2. This is because the cptr value is not 
*   being changed (set to NULL) in the done step so even after freeing the struct, cptr still 
*   points to the freed block of memory.
*   To resolve this bug, I simply set cptr = NULL after it is freed when the user enters 3.
*   I also add a check in the condition statement when the user enters 2 to ensure that 
*   they are not attempting to access the NULL value of cptr after it is freed.
*
*   Multiple free error:
*   Similar to the use-after-free error, the multiple free would occur when the next user
*   attempts to use the previous user's credit card information for themself. After this
*   malicious user is done using the previous user's credit card info and they enter 3 to be
*   done, the program would free the already freed struct causing a double free. 
*   To resolve this bug, I resolved the use-after-free bug and that prevented the double free
*   as they are related.
*/