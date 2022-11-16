#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    /* fork a process */
    int pid = fork();
    int pid2 = fork();
    /* the child and parent will execute every line of code after the fork (each separately)*/
    printf("Hello world, pid:%d pid2:%d!\n", pid, pid2);
    return 0;
}