/* Name: Stephen Tambussi
 * Date: 4/29/2021
 * Title: Lab 5 - Synchronization using semaphores, lock, and condition variables
 * Description: This program provides a solution to the producer-consumer problem
 * using semaphores
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>

#define BUFSIZE 10
#define NP 3 
#define NC 2

pthread_t tidP[NP], tidC[NC];   
int buff[BUFSIZE];
sem_t *mutex, *full, *empty; 
int p, c, in, out; 

void *producer(void *arg) {
    int item;
    int p = (int)arg;
    srand(time(0));
    do {
        item = (rand() % 100);  // random number for producer
        sem_wait(empty); //waits for consumer to empty buffer if fill
        sem_wait(mutex); //enters critical section

       //your code to add item to buffer and increment in index
        buff[in] = item; //adds item to buffer	
        printf ("Producer #: %d produced item: %d at buffer space: %d\n", p, item, in);
	in = (in + 1)%BUFSIZE; //circular buffer - if in reaches end of buffer it will start from beginning
        sleep(3);
        
        sem_post(mutex); //exits critical section
        sem_post(full);
    } while (1);
    pthread_exit(0);
}

void *consumer(void *arg) {
    int item;
    int c = (int)arg;
    srand(time(0));
    do {
        sem_wait(full); //waits for producer to fill buffer if empty
        sem_wait(mutex); //enter critical section

        //you code to remove next item from buffer and increment out index
	item = buff[out]; //removes item
        printf ("\t\t\tConsumer #: %d consumed item: %d at buffer space: %d\n", c, item, out);
	out = (out + 1)%BUFSIZE; //circular buffer - if out reaches end of buffer it will start from beginning
        sleep(3);

        sem_post(mutex); //exits critical section
        sem_post(empty);
    } while (1);
    pthread_exit(0);
}

void cleanup(int sigtype){ //function is invoked if Ctrl-C 
    //destroy semaphores before terminating
    sem_unlink("mutex");
    sem_unlink("empty");
    sem_unlink("full");
    printf("\n Terminating\n");
    exit(0);
}

int main () {
    signal(SIGINT,cleanup); 
    //your code to create mutex, empty, and full semaphores
    mutex = sem_open("mutex", O_CREAT, 0644, 1); //mutex initialized to value = 1
    empty = sem_open("empty", O_CREAT, 0644, BUFSIZE); //empty initialized to value = BUFSIZE(10) (num of empty buffer spaces)
    full = sem_open("full", O_CREAT, 0644, 0); //full initialized to value = 0 (num of filled buffer spaces)   
    for (p = 0; p < NP; p++)
        pthread_create(&tidP[p], NULL, producer, (void *)(size_t)p);
    for (c = 0; c < NC; c++)
        pthread_create(&tidC[c], NULL, consumer, (void *)(size_t)c);
   // main thread waiting for consumer and producer threads to complete their tasks
    for (p = 0; p < NP; p++) {
        pthread_join(tidP[p], NULL);
        printf("Producer thread %d returned\n", p);
    }
    for (c = 0; c < NC; c++) {
        pthread_join(tidC[c], NULL);
        printf("\t\t\tConsumer thread %d returned\n", c);
    }
    printf("Main thread finished\n");
    //destroy semaphores after usage
    sem_unlink("mutex"); 
    sem_unlink("empty");
    sem_unlink("full");
    return 0;
}
