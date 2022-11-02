/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 4
*   10/11/22
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void foo(void)
{
    /*  Heap vs. Stack
    *   - computing cycles consideration
    *   - coding effort consideration
    */
    char stackBuffer[256];
    char *heapBuffer = (char*) malloc(256);
    strcpy(stackBuffer,"abc");
    strcpy(heapBuffer,"abc");
}
void bar()
{
    char Buff[256];
    // do something
}
int main (void)
{
    foo();
    bar();
    /* Malloc Memory Layout */
    char *cp1 = (char*) malloc(1);  //  1-12 has header:0x00000011 = 17, zero out last 3 bits length becomes 0x00000010 = 16
    // Malloc allocates memory starting with 16 bytes and 8 byte increments after that
    char *cp2 = (char*) malloc(12); 
    char *cp3 = (char*) malloc(13); // 13-20 has header:0x00000019 = 25, zero out last 3 bits length becomes 0x00000018 = 24
    char *cp4 = (char*) malloc(20);
    char *cp5 = (char*) malloc(21); // 21-28 has header:0x00000021 = 33, zero out last 3 bits length becomes 0x00000020 = 32
    char *cp6 = (char*) malloc(28);
    printf("main cp1=%p\n",cp1);
    printf("main cp2=%p\n",cp2);
    printf("main cp3=%p\n",cp3);
    printf("main cp4=%p\n",cp4);
    printf("main cp5=%p\n",cp5);
    printf("main cp6=%p\n",cp6);
}

/*
*   Closer look at malloc()
*                   libc       Linux/system calls
*    ---------------------------------------------
*    application -> malloc() -> brk()
*                            -> sbrk()
*                            -> mmap()
*
*
*                        heap
*    [-----------------------------------------------]
*    ^                                               ^
*    |                                               |
*    0x804b000                                   0x806c000
*    initial sbrk(0)                          after 1st malloc
*   - First call to malloc will establish the heap space (more than you will probably need)
*
*   Common Heap Coding Errors:
*   - Not checking return value of malloc
*   - Assuming malloc'd memory is initialized/zeroed
*   - Referencing null or free'd memory
*   - Freeing the same allocated memory more than once
*   - Not freeing --> memory leak
*   
*   Valgrind:
*   - Can detect issues when you are not checking the return value of malloc
*       - If you pass to malloc a value too large for it to allocate, it will return 0
*   - Can detect if allocated memory has not been initialized(zeroed)
*   - Can detect when you are referencing freed/null memory (use-after-free)
*   - Can detect when you are freeing the same memory more than once (multiple free error)
*   - Can detect memory leaks in a program
*   - Can detect overlapping memory writes (strcpy)
*/