/* Name: Stephen Tambussi
 * Date: 4/15/2021
 * Title: Lab3 - Inter-process Communication (IPC) - Pipes
 * Description: This program demonstrates the usage of IPC between processes
 * using pipes to execute the command "ls | sort"
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
//1 = file descriptor of stdout
//0 = file descriptor of stdin
int main()
{
	int fds[2];
	pipe(fds);
	//Child 1 duplicates downstream into stdin
	if(fork() == 0)
	{
		dup2(fds[0], 0); //takes what is going downstream and sends it to stdin
		close(fds[1]); //child 1 closes upstream end of pipe
		execlp("sort", "sort", 0);
	}
	//Child 2 duplicates upstream into stdout
	else if(fork() == 0)
	{
		dup2(fds[1], 1); //takes what is going upstream and sends it to stdout
		close(fds[0]); //child 2 closes downstream end of pipe
		execlp("ls", "ls", 0);
	}
	else //parent closes both ends and waits for children
	{
		close(fds[0]); //parent closes both ends of pipe
		close(fds[1]); 
		wait(0);
		wait(0);
	}
	return 0;
}
