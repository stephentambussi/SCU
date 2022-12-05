/*
 *   Fix deadlock.c so they no longer have deadlocks.
 *
 *   My Solution:
 *      Only use one semaphore instead of two. Code will be less efficient, but it fixes the deadlock
 */
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem4balance1;
//sem_t sem4balance2;
int balance1 = 0;
int balance2 = 0;

void *deposit(void *arg)
{
    int i;
    for (i = 0; i < 10000; i++)
    {
        sem_wait(&sem4balance1); //s4b1 locked
        ++balance1;
        printf("deposit waiting\n");
        //sem_wait(&sem4balance2); //s4b2 locked
        ++balance2;
        //sem_post(&sem4balance2); //s4b2 unlocked
        sem_post(&sem4balance1); //s4b1 unlocked
    }
}
void *withdraw(void *arg)
{
    int i;
    for (i = 0; i < 10000; i++)
    {
        //sem_wait(&sem4balance2); //s4b2 locked
        sem_wait(&sem4balance1);
        ++balance2;
        printf("withdraw waiting\n");
        //sem_wait(&sem4balance1); //s4b1 locked --> deadlocks because deposit thread already has s4b1, but withdraw thread is trying to get it
                                 // so the program stalls because the semaphore is never released
        ++balance1;
        sem_post(&sem4balance1); //s4b1 unlocked
        //sem_post(&sem4balance2); //s4b2 unlocked
    }
}
int main()
{
    pthread_t t1, t2;
    sem_init(&sem4balance1, 0, 1);
    //sem_init(&sem4balance2, 0, 1);
    pthread_create(&t1, NULL, deposit, (void *)1);
    pthread_create(&t2, NULL, withdraw, (void *)2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("all done: balance1 = %d\n", balance1);
    printf("all done: balance2 = %d\n", balance2);
    return 0;
}