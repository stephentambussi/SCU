/* Name: Stephen Tambussi
 * Date: 4/15/2021
 * Title: Lab3 - Inter-process Communication (IPC) - Pipes
 * Description: This program demonstrates the usage of IPC between processes
 * using pipes to send cmd line arguments from one process to another for output
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
//fds[0] = file descriptor on downstream end of pipe
//fds[1] = file descriptor on upstream end of pipe
int main(int argc, char *argv[])
{
	int fds[2];
	char buff[60];
	int count;
	int i;
	pipe(fds);
	if(fork() == 0)
	{
		printf("\nWriter on the upstream end of the pipe -> %d arguments \n", argc);
		close(fds[0]); //closes downstream end of pipe
		for(i = 0; i < argc; i++)
		{
			write(fds[1], argv[i], strlen(argv[i])); //writes cmd line args to upstream end of pipe
		}
		exit(0);
	}
	else if(fork() == 0)
	{
		printf("\nReader on the downstream end of the pipe \n");
		close(fds[1]); //closes upstream end of pipe
		while((count = read(fds[0], buff, 60)) > 0) //reads from downstream end of pipe into buffer(buff)
		{
			for(i = 0; i < count; i++)
			{
				write(1, buff+i, 1); //writes buffer to stdout
				write(1, " ", 1); //adds space between characters
			}
			printf("\n");
		}
		exit(0);
	}
	else //parent closes both ends and waits for children
	{
		close(fds[0]);
		close(fds[1]); 
		wait(0);
		wait(0);
	}
	return 0;
}
