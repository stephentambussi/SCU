/*
*   modify newshell.c such that if the entered command returns a non zero code, the newshell will terminate.
*   For instance, if you enter the cat command below and the file xyz does not exist, the return code is non zero.
*   $ cat xyz
*   cat: xyz: No such file or directory
*   $ echo $?
*   1
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
// Modified get_command to include "echo $?"" to figure out if the return is a non-zero code
int ret_code = 0;
char **get_command(char *input)
{
    char **command = malloc(4 * sizeof(char *));

    command[0] = "sh";
    command[1] = "-c";

    strcat(input, "; echo $? > ret_code.txt"); // Writes return code to a file
    command[2] = input;
    
    command[3] = NULL;
    return command;
}

int main()
{
    char **command;
    char input[256];
    char line[256];
    FILE *fp;
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
            printf("This won't be printed if execvp is successful\n");
        }
        else
        {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }
        
        fp = fopen("ret_code.txt", "r");
        fgets(line, 256, fp);
        ret_code = atoi(line);
        //printf("%d\n", ret_code);

        if(ret_code) break; // newshell terminates when code is non-zero
        
        fclose(fp);
        free(command);
    }

    return 0;
}