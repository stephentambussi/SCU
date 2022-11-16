#include <pthread.h>
#include <stdio.h>
pthread_mutex_t mutex4balance;
int balance = 0;
void *deposit(void *arg)
{
    int i;
    for (i = 0; i < 1000; ++i)
    {
        pthread_mutex_lock(&mutex4balance);
        ++balance;
        pthread_mutex_unlock(&mutex4balance);
    }
}
void *withdraw(void *arg)
{
    int i;
    for (i = 0; i < 1000; ++i)
    {
        pthread_mutex_lock(&mutex4balance);
        --balance;
        pthread_mutex_unlock(&mutex4balance);
    }
}
int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, deposit, (void *)1);
    pthread_create(&t2, NULL, withdraw, (void *)2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("all done: balance = %d\n", balance);
    return 0;
}