/* Stephen Tambussi
 * 1/7/21
 * Lab 1 - C Program with two threads
 * Description: This program practices threading
 */
#include <stdio.h> //printf, stderr
#include <sys/types.h> //pid_t
#include <unistd.h> //fork
#include <stdlib.h> //atoi
#include <errno.h> //errno
#include <pthread.h> //threading
void *thread1(void *n)
{	
	int i;
	for(i = 0; i < 100; i++)
	{
		printf("\t \t \t Thread 1 Process %d \n", i);
		usleep(*((int *) n));
	}
	pthread_exit((void *)n);
}
void *thread2(void *n)
{
	int i;
	for(i = 0; i < 100; i++)
	{
		printf("Thread 2 Process %d \n", i);
		usleep(*((int *) n));
	}
	pthread_exit((void *)n);
}
int main(int argc, char *argv[]) 
{
	pthread_t t1, t2;
	int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
	int *arg = malloc(sizeof(*arg));//allocates memory for delay variable
	*arg = n;
	printf("\n Before Thread. \n");
	pthread_create(&t1, NULL, thread1, arg);//creates 2 threads
	pthread_create(&t2, NULL, thread2, arg);
	pthread_join(t1, (void **)&arg);
	pthread_join(t2, (void **)&arg);
	free(arg);
	return 0;
}
