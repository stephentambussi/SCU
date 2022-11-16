#include <sys/types.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{

    /* fork a child process */
    pid_t cpid = fork();

    if (cpid < 0)
    { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return 1;
    }

    else if (cpid == 0)
    { /* child process */
        printf("I am a child, my pid=%d, my child id=%d\n", getpid(), cpid);
    }

    else
    { /* parent process */
        printf("I am a parent, my pid=%d, my child id=%d\n", getpid(), cpid);
    }
}