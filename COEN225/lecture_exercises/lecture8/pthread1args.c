#include <pthread.h>
#include <stdio.h>
struct thread_data
{
    int sum;
    char *message;
};
void *threadfunction(void *arg)
{
    // Cast the arg to (int*) before use
    struct thread_data *thread_data1ptr = arg;
    printf("thread id:%lu receving arg0:%s\n", pthread_self(), thread_data1ptr->message);
    printf("thread id:%lu receving arg1:%d\n", pthread_self(), thread_data1ptr->sum);
    return (void *)7;
}
int main(void)
{
    pthread_t threadID;
    void *threadresult;
    struct thread_data thread_data1;
    thread_data1.message = "abc";
    thread_data1.sum = 123;

    pthread_create(&threadID, NULL, threadfunction, &thread_data1);
    // The main thread waits the child thread to terminate by calling pthread_join()
    pthread_join(threadID, &threadresult);
    // Only the main thread is running now .
    printf("Child thread:%lu returned %d\n", threadID, (int)threadresult);
    return 0;
}