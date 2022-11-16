#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
pthread_mutex_t m1;
pthread_mutex_t m2;

void *worker1(void *arg)
{
    pthread_mutex_lock(&m1);
    pthread_mutex_lock(&m2);
    pthread_mutex_unlock(&m1);
    pthread_mutex_unlock(&m2);
}
void *worker2(void *arg)
{
    pthread_mutex_lock(&m2);
    pthread_mutex_lock(&m1);
    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);
}

int main()
{
    pthread_t t1, t2;
    int p1arg = 1, p2arg = 2;
    pthread_create(&t1, NULL, worker1, &p1arg);
    pthread_create(&t2, NULL, worker2, &p2arg);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("all done\n");
    return 0;
}