/*
 *   Stephen Tambussi
 *   COEN225
 *   HW4: Memory Leak Detector
 *   11/22/22
 */
#define _GNU_SOURCE
#include <execinfo.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*  GENERAL TODO:
*   - display where malloc, realloc, calloc, free are called in the program (line num)
*   - Print out PID of target process like in valgrind (getpid())
*/

/*  generate_stack_trace()
*   Generates trace at point of call, into tmpfile, and places
*   the trace in the parameter backtracestr
*/
void generate_stack_trace(char *tmpfile, char *backtracestr)
{
    /*  EXTRA CREDIT TODO:
    *   - Show the function names and line numbers
    *   - To do so:
    *       - parse the backtrace.txt to get the executable name and address offset to pass to gdb
    *       - Call system("gdb -batch -ex 'file a.out' -ex 'info line * 0x80484a6' > /tmp/backtrace.gdbout");
    *           - This will generate the function names and line number
    *       - Get the function names and line numbers from .gdbout
    *       - NOTE: need to subtract 1 from the start of the current line
    *            For example,
    *            Given: ./a.out[0x80484a6]
    * 
    *            $ gdb -batch -ex "file a.out" -ex "info line * 0x80484a6"
    *            Line 14 of "doublefree.c" starts at address 0x80484a1  and ends at 0x80484ab .
    * 
    *            ***Line 14 is the line after the call.  To get the line of the call, replace 0x80484a6 by 0x80484a0.
    * 
    *            $ gdb -batch -ex "file a.out" -ex "info line * 0x80484a0"
    *            Line 13 of "doublefree.c" starts at address 0x804849a  and ends at 0x80484a0 .
    */
    void *array[10];
    char **strings;
    int size, i;
    FILE *fp;
    char line[256];
    int f = creat(tmpfile, 0777);
    if (f == -1)
    {
        perror("Failed to create/open a file...\n");
        exit(0);
    }
    size = backtrace(array, 10);
    backtrace_symbols_fd(array, size, f);
    close(f);
    backtracestr[0] = 0;
    fp = fopen(tmpfile, "r");
    while (fgets(line, 256, fp))
    {
        strcat(backtracestr, line);
    }
}

/*  premain()
*   Called before main, used to initialize check_leak data structure  
*/
void __attribute__((constructor)) premain()
{
    //TODO: initialize check_leak data structure (linked list) --> DO THIS FIRST
    fprintf(stderr, "premain\n");
}

/*  realloc()
*   Intercepts calls to the real realloc function to track heap memory
*   chunks
*/
void *realloc(void *ptr, size_t new_size)
{
    static int recursively_called = 0;
    static void *(*real_realloc)(void *, size_t) = NULL;
    void *p;
    if (!recursively_called) //first time called on runtime stack
    {
        //TODO: do leak detection logic here
        recursively_called = 1;
        if (!real_realloc)
            real_realloc = dlsym(RTLD_NEXT, "realloc"); //set to real realloc function via dynamic linker(only happens once due to static ptr)
        p = real_realloc(ptr, new_size);
        recursively_called = 0;
    }
    else //not first time on runtime stack
    {
        p = real_realloc(ptr, new_size);
    }
    return p;
}

/*  calloc()
*   Intercepts calls to the real calloc function to track heap memory
*   chunks
*/
void *calloc(size_t num, size_t size)
{
    static int recursively_called = 0;
    static void *(*real_calloc)(size_t, size_t) = NULL;
    void *p;
    if (!recursively_called) //first time called on runtime stack
    {
        //TODO: do leak detection logic here
        recursively_called = 1;
        if (!real_calloc)
            real_calloc = dlsym(RTLD_NEXT, "calloc"); //set to real calloc function via dynamic linker(only happens once due to static ptr)
        p = real_calloc(num, size);
        recursively_called = 0;
    }
    else //not first time on runtime stack
    {
        p = real_calloc(num, size);
    }
    return p;
}

/*  malloc()
*   Intercepts calls to the real malloc function to track heap memory
*   chunks
*/
void *malloc(size_t size)
{
    static int recursively_called = 0;
    static void *(*real_malloc)(size_t) = NULL;
    void *p;
    int f;
    if (!recursively_called) //first time called on runtime stack
    {
        //TODO: do leak detection logic here
        recursively_called = 1;
        if (!real_malloc)
            real_malloc = dlsym(RTLD_NEXT, "malloc"); //set to real malloc function via dynamic linker(only happens once due to static ptr)

        p = real_malloc(size);
        fprintf(stderr, "malloc(%d) = %p\n", size, p);
        recursively_called = 0;
    }
    else //not first time on runtime stack
    {
        p = real_malloc(size);
    }
    return p;
}

/*  free()
*   Intercepts calls to the real free function to track heap memory
*   chunks
*/
void free(void *p)
{
    static int recursively_called = 0;
    static void (*real_free)(void *) = NULL;
    char backtracestr[4096];
    if (!recursively_called) //first time called on runtime stack
    {
        //TODO: do leak detection logic here
        recursively_called = 1;
        if (!real_free)
            real_free = dlsym(RTLD_NEXT, "free"); //set to real free function via dynamic linker(only happens once due to static ptr)
        real_free(p);
        fprintf(stderr, "free(%p)\n", p);
        /*
          uncomment the next 2 lines to see how generate_stack_trace() works
        */
        //generate_stack_trace("/tmp/backtrace.txt", backtracestr); //TODO: change file path
        //fprintf(stderr, "%s", backtracestr);
        recursively_called = 0;
    }
    else //not first time on runtime stack
    {
        real_free(p);
    }
}

/*  postmain()
*   Called after main, used to print out the summary before program exit  
*/
void __attribute__((destructor)) postmain()
{
    //TODO: print out summary before program exit
    fprintf(stderr, "postmain\n");
}

/*  Tasks:

    1. Your program will print out a summary of the memory leaks in a C program. 
    Ideally, each loss should be noted similar to the --leak-check=full valgrind option:
    stack trace, file names and lines (see sample below).
    However, you can submit without the stack trace if you are out of time.

    2. Your program will also intercept invalid free (such as free after free) calls,
    by preventing the free calls after the first valid free, from crashing the program.
    Instead, you will show the invalid free attempts at the summary.

    Valgrind Output for Comparison:
  PID
==1518== Memcheck, a memory error detector
==1518== Copyright (C) 2002-2015, and GNU GPL'd, by Julian Seward et al.
==1518== Using Valgrind-3.11.0 and LibVEX; rerun with -h for copyright info
==1518== Command: ./a.out
==1518== 
==1518== Invalid free() / delete / delete[] / realloc()
==1518==    at 0x402E358: free (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==1518==    by 0x8048479: foo (doublefree.c:9)
==1518==    by 0x80484A5: main (doublefree.c:14)
==1518==  Address 0x41f9068 is 0 bytes inside a block of size 16 free'd
==1518==    at 0x402E358: free (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==1518==    by 0x804846B: foo (doublefree.c:8)
==1518==    by 0x80484A5: main (doublefree.c:14)
==1518==  Block was alloc'd at
==1518==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==1518==    by 0x804844A: foo (doublefree.c:6)
==1518==    by 0x80484A5: main (doublefree.c:14)
==1518== 
==1518== 
==1518== HEAP SUMMARY:
==1518==     in use at exit: 48 bytes in 2 blocks
==1518==   total heap usage: 3 allocs, 2 frees, 64 bytes allocated
==1518== 
==1518== 16 bytes in 1 blocks are definitely lost in loss record 1 of 2
==1518==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==1518==    by 0x804849A: main (doublefree.c:13)
==1518== 
==1518== 32 bytes in 1 blocks are definitely lost in loss record 2 of 2
==1518==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==1518==    by 0x804845A: foo (doublefree.c:7)
==1518==    by 0x80484A5: main (doublefree.c:14)
==1518== 
==1518== LEAK SUMMARY:
==1518==    definitely lost: 48 bytes in 2 blocks
==1518==    indirectly lost: 0 bytes in 0 blocks
==1518==      possibly lost: 0 bytes in 0 blocks
==1518==    still reachable: 0 bytes in 0 blocks
==1518==         suppressed: 0 bytes in 0 blocks
==1518== 
==1518== For counts of detected and suppressed errors, rerun with: -v
==1518== ERROR SUMMARY: 3 errors from 3 contexts (suppressed: 0 from 0)
*/