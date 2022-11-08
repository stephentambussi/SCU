/*
*   This program is used as an example to intercept dynamic library functions
*   - Associated with unrandom.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int correct = 0;
    int r;
    int guess;
    while (!correct)
    {
        r = rand() % 100;
        printf("give me a guess:");
        scanf("%d", &guess);
        printf("You guess:%d answer:%d\n", guess, r);
        if (guess == r)
            correct = 1;
    }
    return 0;
}

/*
*   To run this:
*       $ gcc randomgame.c (creates a.out)
*       $ gcc -g -shared -fPIC unrandom.c -o unrandom.so
*       $ LD_PRELOAD=$PWD/unrandom.so ./a.out
*/