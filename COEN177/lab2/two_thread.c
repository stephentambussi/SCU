/* Name: Stephen Tambussi
 * Date: 4/8/2021
 * Title: Lab2 - C Programming and System Calls
 * Description: This program demonstrates the usage of threads
 */
#include <stdio.h> //printf, stderr
#include <sys/types.h> //pid_t
#include <unistd.h> //fork
#include <stdlib.h> //atoi
#include <errno.h> //errno
#include <pthread.h> //threads
void *thread1(void *n) //thread 1 function
{
	int i;
	for(i = 0; i < 100; i++)
	{
		printf("\t \t \t Thread 1 %d \n", i);
		//typecast the void pointer to an int pointer and then dereference it
		usleep(*((int *) n)); 
	}
	pthread_exit((void *)n);
}
void *thread2(void *n) //thread 2 function
{
	int i;
	for(i = 0; i < 100; i++)
	{
		printf("Thread 2 %d \n", i);
		usleep(*((int *) n));
	}
	pthread_exit((void *)n);
}
int main(int argc, char *argv[])
{
	pthread_t t1, t2;
	int i, n = atoi(argv[1]); //n microseconds to input from keyboard for delay
	int *arg = malloc(sizeof(*arg)); //allocates memory for delay variable
	*arg = n; //sets the value of the pointer
	printf("\n Before Thread. \n");
	//create 2 threads
	pthread_create(&t1, NULL, thread1, arg);
	pthread_create(&t2, NULL, thread2, arg);
	pthread_join(t1, (void **)&arg);
	pthread_join(t2, (void **)&arg);
	free(arg); //free allocated memory
	return 0;
}
