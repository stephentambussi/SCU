#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
// get_command parses "ls -l -a" into command[] = { "ls", "-l", "-a", NULL } to pass to execvp()
char **get_command(char *input)
{
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL)
    {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}
int main()
{
    char **command;
    char input[256];
    pid_t child_pid;
    int stat_loc;
    int len;
    int read;

    while (printf("newshell$ "), fgets(input, 60, stdin) != NULL)
    {
        input[strlen(input) - 1] = '\0';

        command = get_command(input);

        child_pid = fork();
        if (child_pid == 0)
        {
            /* Never returns if the call is successful */
            execvp(command[0], command);
            printf("This won't be printed if execvp is successul\n");
        }
        else
        {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(command);
    }

    return 0;
}