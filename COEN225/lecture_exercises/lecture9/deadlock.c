/*
 *   This program shows a deadlock in action
 */
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem4balance1;
sem_t sem4balance2;
int balance1 = 0;
int balance2 = 0;
void *deposit(void *arg)
{
    int i;
    for (i = 0; i < 1000000; i++)
    {
        sem_wait(&sem4balance1);
        ++balance1;
        printf("deposit waiting\n");
        sem_wait(&sem4balance2);
        ++balance2;
        sem_post(&sem4balance2);
        sem_post(&sem4balance1);
    }
}
void *withdraw(void *arg)
{
    int i;
    for (i = 0; i < 1000000; i++)
    {
        sem_wait(&sem4balance2);
        ++balance2;
        printf("withdraw waiting\n");
        sem_wait(&sem4balance1);
        ++balance1;
        sem_post(&sem4balance1);
        sem_post(&sem4balance2);
    }
}
int main()
{
    pthread_t t1, t2;
    sem_init(&sem4balance1, 0, 1);
    sem_init(&sem4balance2, 0, 1);
    pthread_create(&t1, NULL, deposit, (void *)1);
    pthread_create(&t2, NULL, withdraw, (void *)2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("all done: balance1 = %d\n", balance1);
    printf("all done: balance2 = %d\n", balance2);
    return 0;
}