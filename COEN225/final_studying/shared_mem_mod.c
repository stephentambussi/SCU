/*
*   how can we modify forkipc.c (shared_mem.c) such that parent process places a string in shared memory 
*   for child process to convert to upper case, in the same shared memory?
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

void *create_shared_memory(size_t size)
{
    // Our memory buffer will be readable and writable:
    int protection = PROT_READ | PROT_WRITE;

    // The buffer will be shared (meaning other processes can access it), but
    // anonymous (meaning third-party processes cannot obtain an address for it),
    // so only this process and its children will be able to use it:
    int visibility = MAP_SHARED | MAP_ANONYMOUS;

    // The remaining parameters to `mmap()` are not important for this use case,
    // but the manpage for `mmap` explains their purpose.
    return mmap(NULL, size, protection, visibility, -1, 0);
}
#include <string.h>
#include <unistd.h>

int main()
{
    char parent_message[] = "hello";  // parent process will write this message
    char upper_case[32];

    void *shmem = create_shared_memory(128);

    memcpy(shmem, parent_message, sizeof(parent_message)); // parent process places string in shared memory

    int pid = fork();

    if (pid == 0) // Child process
    {
        printf("Child read: %s\n", shmem);
        memcpy(upper_case, shmem, sizeof(shmem));
        for(int i = 0; i < strlen(upper_case); i++)
        {
            upper_case[i] -= 32;
        }
        //printf("%s\n", upper_case);
        memcpy(shmem, upper_case, sizeof(upper_case));
        printf("Child wrote: %s\n", shmem);
    }
    else // Parent process
    {
        printf("Parent read: %s\n", shmem);
        sleep(1);
        printf("After 1s, parent read: %s\n", shmem);
    }
}