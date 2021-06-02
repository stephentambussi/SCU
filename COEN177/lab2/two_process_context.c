/* Name: Stephen Tambussi
 * Date: 4/8/2021
 * Title: Lab2 - C Programming and System Calls
 * Description: This program demonstrates the usage of parent and child processes
 * running separate code (changing the context).
 */
#include <stdio.h> //printf, stderr
#include <sys/types.h> //pid_t
#include <unistd.h> //fork
#include <stdlib.h> //atoi
#include <errno.h> //errno
//Main function with command-line arguments to pass
int main(int argc, char *argv[])
{
	pid_t pid;
	printf("\n Before Forking.\n");
	pid = fork(); //creates child process
	if(pid == -1) //error check
	{
		fprintf(stderr, "can't fork: error %d\n", errno);
	}
	if(pid == 0) //Child process
	{
		execlp("/bin/ls", "ls", NULL);
	}
	else //Parent process
	{
		wait(NULL);
		printf("Child Process Complete\n");
		exit(0);
	}
	return 0;
}
