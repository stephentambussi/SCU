#include <pthread.h>
#include <stdio.h>
int balance = 0;
void *deposit(void *arg)
{
    int i;
    for (i = 0; i < 1e7; ++i)
        ++balance;
}
void *withdraw(void *arg)
{
    int i;
    for (i = 0; i < 1e7; ++i)
        --balance;
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

/*
A data races situation:

thread1 for deposit:                   thread2 for withdraw:
------------------------------------------------------------
mov    balance,%eax
add    $0x1,%eax
                                       mov    balance,%eax
                                       sub    $0x1,%eax
                                       mov    %eax,balance

mov    %eax,balance
*/