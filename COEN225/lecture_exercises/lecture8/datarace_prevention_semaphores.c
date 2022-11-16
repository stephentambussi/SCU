#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

sem_t sem4balance;
pthread_mutex_t mutex4balance;
int balance = 0;
void *deposit(void *arg)
{
    int i;
    for (i = 0; i < 100000000; ++i)
    {
        sem_wait(&sem4balance);
        ++balance;
        sem_post(&sem4balance);
    }
}
void *withdraw(void *arg)
{
    int i;
    for (i = 0; i < 100000000; ++i)
    {
        sem_wait(&sem4balance);
        --balance;
        sem_post(&sem4balance);
    }
}
int main()
{
    pthread_t t1, t2;
    sem_init(&sem4balance, 0, 1);
    pthread_create(&t1, NULL, deposit, (void *)1);
    pthread_create(&t2, NULL, withdraw, (void *)2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("all done: balance = %d\n", balance);
    return 0;
}