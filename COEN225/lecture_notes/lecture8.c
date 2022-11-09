/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 8
*   11/8/22
*/
#include <stdio.h>
#include <string.h>

int main()
{
    return 0;
}

/*
*   TOOD: do study questions for final from this lecture
*   
*   Concurrency vs. Parallelism
*   - You already know this
*     Concurrency: running multiple programs at once, but not necessarily executing at the same instantaneous point in time
*       - Think of a person juggling tennis balls
*     Parallelism: running multiple programs at the same time, meaning multiple processes are executing at a single point in time
*       - Think of watching a movie and eating popcorn (two activities occuring at the same points in time)
*
*   Process vs. Thread
*   - Process is an instance of a program in execution, loaded from disk to memory
*   - Thread is an executing segment of a process, either main thread that started with process
*     or child thread that was spawned later
*
*   Process Creation
*   - You already know this
*   - fork() will create 1 new process that is a copy of the current program and
*     will continue execution at the point in the program when fork was called
*   - Number of processes created is roughly equivalent to 2^n, where n is the number of fork calls
*       - This can vary depending on how if statements are implemented
*     fork() return values:
*        0 -> current process is the created child process
*       >0 -> current process is the parent process that called fork
*
*   Inter-process communication (IPC)
*   - You already know this
*     Types:
*       - Pipes
*       - Message queues
*       - Shared memory (mmap)
*           - TODO: review code for this part of lecture
*   
*   Thread Creation
*   - You already know this
*   - pthreads
*       - To pass multiple arguments to a thread function, use a struct
*
*   Data races or Race condition (caused by no synchronization)
*   - Occurs when multiple threads or processes try to access a shared variable
*   - Helgrind: thread error detector 
*       - Can detect data race conditions in programs
*   - pthread_mutex_trylock() -- TODO: review this
*   - condition variables -- TODO: review this
*/