#include <pthread.h>
#include <stdio.h>
/*
 * The function to be executed by the thread should take a
 * void * parameter and return a void * result .
 */
void *threadfunction(void *arg)
{
    // Cast the arg to (int*) before use
    printf("thread id:%lu receving arg:%d\n", pthread_self(), *(int *)arg);
    sleep(*(int *)arg);
    return (void *)7;
}
int main(void)
{
    pthread_t threadID;
    int value;
    void *threadresult;
    value = 5;
    // Create the thread , calling threadfunction(&value)
    pthread_create(&threadID, NULL, threadfunction, &value);
    // The main thread waits the child thread to terminate by calling pthread_join()
    pthread_join(threadID, &threadresult);
    // Only the main thread is running now .
    printf("Child thread:%lu returned %d\n", threadID, (int)threadresult);
    return 0;
}