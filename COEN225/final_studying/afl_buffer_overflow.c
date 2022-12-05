/*
*   Write a small program with a buffer overflow vulnerability.
*   Compile it using AFL-GCC.
*   Fuzz it using AFL-FUZZ for one hour.
*   Report numbers of the crashing and hanging test cases.
*   Try the test cases out and see if they indeed produce the crashes or hangs.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input1[16];
char password[16];

int main(int argc, char **argv)
{
    strcpy(password,"california");
    
    if(argc > 1) // Safe 
    {
        FILE *fp = fopen(argv[1], "r");
        fgets(input1, sizeof(input1), fp);
        fclose(fp);
    }
    else    // Unsafe -- vulnerable to buffer overflow
    {
        gets(input1);
    }

    printf("Entered password: %s\n", input1);

    if (strcmp(input1,password)==0) {
        printf("you guessed right!\n");
        return 0;
    }
    else
    {
        printf("you guessed wrong!\n");
        return 0;
    }
}