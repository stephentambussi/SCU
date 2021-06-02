/* Name: Stephen Tambussi
 * Date: 4/15/2021
 * Title: Lab3 - Inter-process Communication (IPC) - Pipes
 * Description: This program demonstrates a producer-consumer problem example using pipes
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
	memset(buff, 0, sizeof(buff));
	//creates pipe
	pipe(fds);
	printf("Input a sentence to send to consumer: \n");
	fgets(buff, sizeof(buff), stdin); //read from stdin into buff
	//creates producer by forking
	if(fork() == 0)
	{
		printf("Producer on upstream end of pipe. \n");
		close(fds[0]); //closes downstream end of pipe
		write(fds[1], buff, 60); //takes user input stored in buffer and sends it to upstream end of pipe 
		exit(0);
	}
	//create consumer by forking
	else if(fork() == 0)
	{
		printf("\nConsumer on downstream end of pipe \n");
		close(fds[1]); //closes upstream end of pipe
		while((count = read(fds[0], buff, 60)) > 0) //reads from downstream end of pipe into buffer(buff)
		{
			for(i = 0; i < count; i++)
			{
				write(1, buff+i, 1); //writes buffer to stdout
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
