/* Name: Stephen Tambussi
 * Date: 4/8/2021
 * Title: Lab2 - C Programming and System Calls
 * Description: This program demonstrates how to create exactly 7 processes
 */
#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid1, pid2;
	pid1 = fork(); //creates first child
	//Creates 2nd child. First child also executes this and creates 1 grandchild
	pid2 = fork(); 

	if(pid1 > 0 && pid2 > 0)
	{
		printf("Parent with ID: %d \n", getpid());
	}

	if(pid1 == 0 && pid2 > 0) //first child
	{
		printf("Child with ID: %d and Parent ID: %d \n", getpid(), getppid());
		pid2 = fork(); //creates 2nd child for first child(1 more grandchild)
	}
	if(pid1 > 0 && pid2 == 0) //second child
	{
		printf("Child with ID: %d and Parent ID: %d \n", getpid(), getppid());
		//second child will create two children (2 more grandchildren)
		pid1 = fork(); //create first child of 2nd child of parent
	       	if(pid1 > 0) //if it is still the second child
		{
			pid2 = fork(); //create 2nd child of 2nd child of parent
			pid1 = 0;
		}
	}
	if(pid1 == 0 && pid2 == 0)
	{
		printf("Child with ID: %d and Parent ID: %d \n", getpid(), getppid());
	}
	return 0;	
}
