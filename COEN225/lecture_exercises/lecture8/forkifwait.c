#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    pid_t cpid, w;
    int status;

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0)
    { /* Code executed by child */
        printf("Child PID is %ld\n", (long)getpid());
        if (argc == 1)
            sleep(100000); /* Wait for signals */
        _exit(atoi(argv[1]));
    }
    else
    { /* Code executed by parent */
        w = waitpid(cpid, &status, 0);
        if (w == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status))
        {
            printf("exited, status=%d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("killed by signal %d\n", WTERMSIG(status));
        }
        exit(EXIT_SUCCESS);
    }
}