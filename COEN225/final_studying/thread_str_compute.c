/*
*    Write a program that passes 3 parameters like "xyz", 12, 0.5 to a child thread
*    and have it compute a string being "xyz"*(int)12*0.5 = "xyzxyzxyzxyzxyzxyz" and 
*    return it.
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct thread_args
{
    char str[64];
    int num1;
    double num2;
};

char *result;

void *thread_computer(void *arg)
{
    struct thread_args *arg_ptr = arg;
    int cat_times = (int) arg_ptr->num1 * arg_ptr->num2;
    int alloc_amount = strlen(arg_ptr->str) * cat_times;
    //printf("%d\n", alloc_amount);
    result = (char *) malloc(alloc_amount * sizeof(char));
    for(int i = 0; i < cat_times; i++)
    {
        strcat(result, arg_ptr->str);
    }
    return result;
}

int main(int argc, char **argv)
{
    pthread_t threadID;
    struct thread_args args1;
    void *threadresult;

    if(argc == 4)
    {
        strcpy(args1.str, argv[1]);
        args1.num1 = atoi(argv[2]);
        args1.num2 = atof(argv[3]);
    }
    else
    {
        printf("Wrong number of args\n");
        return -1;
    }

    pthread_create(&threadID, NULL, thread_computer, &args1);
    pthread_join(threadID, &threadresult);

    printf("Thread: %lu returned %s\n", threadID, (char *)threadresult);
    free(result);
    return 0;
}