/* Name: Stephen Tambussi
 * Date: 4/29/2021
 * Title: Lab5 - Synchronization using semaphores, lock, and condition variables
 * Description: This program provides an example of thread synchronization using
 * mutex locks
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>  

#define NTHREADS 10
pthread_t threads[NTHREADS];
pthread_mutex_t m;

void* go(void* arg) { 
  	pthread_mutex_lock(&m); //entry section
  	printf("Thread %d Entered Critical Section..\n", (int)arg); //critical section 
  	sleep(1); 
  	pthread_mutex_unlock(&m); //exit section 
  	return (NULL);
} 

int main() {
       	pthread_mutex_init(&m, NULL);	
	static int i;
	for (i = 0; i < NTHREADS; i++)  
   		pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
	for (i = 0; i < NTHREADS; i++) {
   		pthread_join(threads[i],NULL);
   		printf("\t\t\tThread %d returned \n", i);
	}
	printf("Main thread done.\n");
	pthread_mutex_destroy(&m);
	return 0; 
} 
