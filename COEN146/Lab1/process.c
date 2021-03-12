/* Stephen Tambussi
 * 1/7/21
 * Lab 1 - C Program with two processes
 * Description: This program practices system calls by creating processes
 */
#include <stdio.h> //printf, stderr
#include <sys/types.h> //pid_t
#include <unistd.h> //fork
#include <stdlib.h> //atoi
#include <errno.h> //errno
int main(int argc, char *argv[]) 
{
	pid_t pid;
	int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
	printf("\n Before Forking. \n");
	pid = fork();
	if(pid == -1)
	{
		fprintf(stderr, "can't fork, error %d\n", errno);
	}
	if(pid) 
	{
		//Parent process
		for(i = 0; i < 100; i++)
		{
			printf("\t \t \t Parent Process %d \n", i);
			usleep(n); //stops execution for n microseconds
		}
	}
	else
	{
		//Child process
		for(i = 0; i < 100; i++)
		{
			printf("Child process %d\n", i);
			usleep(n);
		}
	}
	return 0;
}
