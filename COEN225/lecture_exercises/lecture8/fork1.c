#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    /* fork a process */
    int pid = fork();
    /* the child and parent will execute every line of code after the fork (each separately)*/
    printf("Hello world, my forked child is:%d with address:%p!\n", pid, &pid);
    return 0;
}