/* Name: Stephen Tambussi
 * Date: 4/8/2021
 * Title: Lab2 - C Programming and System Calls
 * Description: This program demonstrates the usage of parent and child processes
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
	int i, n = atoi(argv[1]); //n microseconds to input from keyboard for delay
	printf("\n Before Forking.\n");
	pid = fork(); //creates child process
	if(pid == -1) //error check
	{
		fprintf(stderr, "can't fork: error %d\n", errno);
	}
	if(pid) //Parent process
	{
		for(i = 0; i < 100; i++)
		{
			printf("\t \t \t Parent Process %d \n", i);
			usleep(n); //sleep command
		}
	}
	else //Child process
	{
		for(i = 0; i < 100; i++)
		{
			printf("Child process %d \n", i);
			usleep(n);
		}
	}
	return 0;
}
