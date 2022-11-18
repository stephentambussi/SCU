/*
 *   Stephen Tambussi
 *   COEN225
 *   HW4: Memory Leak Detector
 *   11/29/22
 * 
 *   TO RUN:
 *      1) Run "make"
 *      2) Compile one of the tests: "gcc -g test1.c"
 *      3) Run a.out using custom library: "LD_PRELOAD=$PWD/check_leak.so ./a.out"
 */
//NOTE: this program is a prototype, it only needs to work on the 5 test cases
#define _GNU_SOURCE
#define N 40        // Max size of memory tracking array
#define DEBUG 0     // 0 = debug messages off | 1 = debug messages on

#include <execinfo.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

// 'Linked list' to track allocated blocks
struct allocatedMem {
    size_t block_size;
    void *memAddr;      // Address that points to allocated block
    int freed;          // -1 = never used | 0 = still allocated | 1 = already freed 
};

struct allocatedMem blocks[N]; // Array of structs (Linked List) to track allocated blocks
int lastUsed = 0;              // Keeps track of last allocated block index (for efficiency purposes)

// Global variables to keep track of total allocated mem, allocs, and frees
int numAllocs = 0;
int numFrees = 0;
size_t allocatedBytes = 0;    // This keeps track of total heap usage, regardless of frees

// Misc. global variables
char pid[10];
int this_is_printf = 0;             // This flag tells malloc that the calling function is printf
void *printf_buffer_addr = NULL;    // This tells the program the mem addr of the printf buffer for cleanup

/*  generate_stack_trace()
*   Generates trace at point of call, into tmpfile, and places
*   the trace in the parameter backtracestr
*/
void generate_stack_trace(char *tmpfile, char *backtracestr)
{
    if(DEBUG) fprintf(stderr, "++DEBUG++ Start of generate_stack_trace()\n");
    /*  EXTRA CREDIT TODO:
    *   - Show the function names and line numbers
    *   - How to do so:
    *       - Call system("gdb -batch -ex 'file a.out' -ex 'info line * 0x80484a6' > /tmp/backtrace.gdbout");
    *           - This will generate the function names and line number
    *       - Get the function names and line numbers from .gdbout
    *       - NOTE: need to subtract 1 from the start of the current line
    *            For example,
    *            Given: ./a.out[0x80484a6]
    * 
    *            $ gdb -batch -ex "file a.out" -ex "info line * 0x80484a6"
    *            Line 14 of "doublefree.c" starts at address 0x80484a1  and ends at 0x80484ab.
    * 
    *            ***Line 14 is the line after the call.  To get the line of the call, replace 0x80484a6 by 0x80484a0.
    * 
    *            $ gdb -batch -ex "file a.out" -ex "info line * 0x80484a0"
    *            Line 13 of "doublefree.c" starts at address 0x804849a  and ends at 0x80484a0.
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
    backtrace_symbols_fd(array, size, f); // This will write the backtrace to the tmpfile
    close(f);
    backtracestr[0] = 0;
    fp = fopen(tmpfile, "r");
    //while(fgets(line, 256, fp))
    //{
        //char filename[10];
        //char *offset;
        //char system_str[100];
        //For simplicity, making assumption that executable name is always "a.out"
        //if(strncmp(line, "./a.out", 7) == 0)
        //{
            //strcpy(filename, "a.out");
            //offset = strtok(line, "[");
            //offset = strtok(NULL, "]");
            
            //sprintf(system_str, "gdb -batch -ex 'file %s' -ex 'info line * %s' > backtrace.gdbout", filename, offset);
            //system(system_str);
            //fprintf(stderr, "%s\n", system_str);
        //}
        //if(strncmp(line, "/lib/", 5) == 0) //stop detector
        //{
        //    break;
        //}
    //}
    /*
    fp = fopen(tmpfile, "r");
    // The below will read from the tmpfile and add to the backtracestr --> THIS SHOULD BE DONE LAST
    while (fgets(line, 256, fp))
    {
        strcat(backtracestr, line);
    }
    */
    fclose(fp);
}

/*  premain()
*   Called before main, used to initialize check_leak data structure  
*/
void __attribute__((constructor)) premain()
{
    for(int x = 0; x < N; x++) // Initialize each block of struct array
    {
        blocks[x].block_size = 0;
        blocks[x].memAddr = NULL;
        blocks[x].freed = -1;
    }
    numAllocs = 0;
    numFrees = 0;
    allocatedBytes = 0;
    memset(pid, ' ', 10);
    sprintf(pid, "==%ld==", (long)getpid());
    
    fprintf(stderr, "%s A Memory Error Detector Program\n", pid);
    fprintf(stderr, "%s Created by Stephen Tambussi for COEN225\n", pid);
    fprintf(stderr, "%s\n", pid);
}

/*  printf()
*   Intercepts calls to the real printf function to help track heap memory.
*   By default, printf allocates a buffer which affected the program's memory
*   tracking since it strangely did not also call free to release the buffer.
*   This intercepting function will call free for the allocated printf buffer.
*/
int printf(const char *format, ...)
{
    this_is_printf = 1;
    int result;
    va_list ap;             // This means there can be many additional args following *format
    va_start(ap, format);

    if(DEBUG && printf_buffer_addr == NULL) 
        fprintf(stderr, "++DEBUG++ Before printf buffer malloc\n");

    result = vprintf(format, ap);
    va_end(ap);

    this_is_printf = 0;
    return result;
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
    if (!recursively_called)    // First time called on runtime stack
    {
        void *prev = ptr;       // Need to save ptr since realloc might mess with it behind the scenes
        recursively_called = 1;
        if (!real_realloc)
            real_realloc = dlsym(RTLD_NEXT, "realloc"); //set to real realloc function via dynamic linker(only happens once due to static ptr)
        p = real_realloc(ptr, new_size);

        if(DEBUG) fprintf(stderr, "++DEBUG++ %p = realloc(%p, %zu) called inside if\n", p, ptr, new_size);

        // 2 Cases: either realloc allocates new memory and frees old block OR resize original block 'in-place'
        if(p != prev)        // Since p points to another address, a new block of memory must have been allocated or ptr was NULL
        {
            if(prev == NULL) // If ptr(prev) was NULL, realloc acts like malloc
            {
                if(lastUsed < N)
                {
                    blocks[lastUsed].block_size = new_size;
                    blocks[lastUsed].memAddr = p;
                    blocks[lastUsed].freed = 0;
                    lastUsed++;

                    numAllocs++;
                    allocatedBytes += new_size;
                }
                else
                {
                    fprintf(stderr, "##ERROR## program has reached the limit of memory tracking size --> INCREASE N\n");
                }
            }
            else // In this case, realloc allocates a new mem block, copies the data, and frees the old block
            {
                if(lastUsed < N)
                {
                    blocks[lastUsed].block_size = new_size;
                    blocks[lastUsed].memAddr = p;
                    blocks[lastUsed].freed = 0;
                    lastUsed++;

                    numAllocs++;
                    allocatedBytes += new_size;

                    for(int x = 0; x < N; x++) // Don't actually call free, since real_realloc already called it
                    {
                        if(prev == blocks[x].memAddr && blocks[x].freed == 1) // Invalid free
                        {
                            fprintf(stderr, "%s Invalid free: free(%p)\n", pid, p); //TODO: get line that this is called
                            numFrees++;
                            break;
                        }
                        else if(prev == blocks[x].memAddr && blocks[x].freed == 0) // Valid free
                        {
                            blocks[x].freed = 1; // Set to freed state
                            numFrees++;
                            break;
                        }
                    }
                }
                else
                {
                    fprintf(stderr, "##ERROR## program has reached the limit of memory tracking size --> INCREASE N\n");
                }
            }
        }
        else // p = ptr, which means that realloc is resizing the original block 'in-place'
        {
            int flag = 0;
            for(int x = 0; x < N; x++)
            {
                if(p == blocks[x].memAddr && blocks[x].freed == 0)
                {
                    size_t previous_size = blocks[x].block_size;
                    blocks[x].block_size = new_size;

                    allocatedBytes += (int) new_size - previous_size; // TODO: account for realloc reducing the size of mem block (neg)
                    numAllocs++;
                    flag = 1;
                    break;
                }
            }
            //TODO: is the below needed?
            if(flag == 0) // If the loop finished without matching any address
            {
                // Program is attempting to realloc with invalid address
                fprintf(stderr, "%s Invalid address with realloc(): %p\n", pid, p); //TODO: get line that this is called
            }
        }

        recursively_called = 0;
    }
    else //not first time on runtime stack
    {
        p = real_realloc(ptr, new_size);
        if(DEBUG) fprintf(stderr, "++DEBUG++ %p = realloc(%p, %zu) called inside else\n", p, ptr, new_size);
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
    if (!recursively_called) // First time called on runtime stack
    {
        recursively_called = 1;
        if (!real_calloc)
            real_calloc = dlsym(RTLD_NEXT, "calloc"); //set to real calloc function via dynamic linker(only happens once due to static ptr)
        p = real_calloc(num, size);

        if(DEBUG) fprintf(stderr, "++DEBUG++ %p = calloc(%zu, %zu) called inside if\n", p, num, size);

        if(lastUsed < N)
        {
            blocks[lastUsed].block_size = num * size; // This is the primary difference between malloc
            blocks[lastUsed].memAddr = p;
            blocks[lastUsed].freed = 0;
            lastUsed++;

            numAllocs++;
            allocatedBytes += num * size;
        }
        else
        {
            fprintf(stderr, "##ERROR## program has reached the limit of memory tracking size --> INCREASE N\n");
        }

        recursively_called = 0;
    }
    else // Not first time on runtime stack
    {
        p = real_calloc(num, size);
        if(DEBUG) fprintf(stderr, "++DEBUG++ %p = calloc(%zu, %zu) called inside else\n", p, num, size);
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
    if (!recursively_called) // First time called on runtime stack
    {
        recursively_called = 1;
        if (!real_malloc)
            real_malloc = dlsym(RTLD_NEXT, "malloc"); //set to real malloc function via dynamic linker(only happens once due to static ptr)
        p = real_malloc(size);

        if(DEBUG) fprintf(stderr, "++DEBUG++ %p = malloc(%zu) called inside if\n", p, size);

        if(lastUsed < N)
        {
            blocks[lastUsed].block_size = size;
            blocks[lastUsed].memAddr = p;
            blocks[lastUsed].freed = 0;
            allocatedBytes += size;
            // Set printf_buffer_index so destructor can free the printf buffer
            if(this_is_printf) printf_buffer_addr = p;
            lastUsed++;
            numAllocs++;
        }
        else
        {
            fprintf(stderr, "##ERROR## program has reached the limit of memory tracking size --> INCREASE N\n");
        }

        recursively_called = 0;
    }
    else // Not first time on runtime stack
    {
        p = real_malloc(size);
        if(DEBUG) fprintf(stderr, "++DEBUG++ %p = malloc(%zu) called inside else\n", p, size);
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
    if (!recursively_called) // First time called on runtime stack
    {
        recursively_called = 1;
        if (!real_free)
            real_free = dlsym(RTLD_NEXT, "free"); //set to real free function via dynamic linker(only happens once due to static ptr) 

        if(DEBUG) fprintf(stderr, "++DEBUG++ free(%p) called inside if\n", p);

        int flag = 0;
        for(int x = 0; x < N; x++)
        {
            if(p == blocks[x].memAddr && blocks[x].freed == 1) // Invalid free
            {
                fprintf(stderr, "%s Invalid free: free(%p)\n", pid, p); //TODO: get line that this is called
                numFrees++;
                flag = 1;
                break;
            }
            else if(p == blocks[x].memAddr && blocks[x].freed == 0) // Valid free
            {
                real_free(p); // First, call the real free
                blocks[x].freed = 1; // Then, set block to freed state
                numFrees++;
                flag = 1;
                break;
            }
        }
        //TODO: check if free should still be counted even if the address was incorrect like below?
        if(flag == 0) // If the loop finished without matching any address
        {
            // Program is attempting to free with invalid address or
            // on memory that was never allocated before
            fprintf(stderr, "%s Invalid address for free(): %p\n", pid, p); //TODO: get line that this is called
        }

        /*
          uncomment the next 2 lines to see how generate_stack_trace() works
        */
        //generate_stack_trace("backtrace.txt", backtracestr);
        //fprintf(stderr, "%s", backtracestr);
        recursively_called = 0;
    }
    else // Not first time on runtime stack
    {
        if(DEBUG) fprintf(stderr, "++DEBUG++ free(%p) called inside else\n", p);

        //TODO: check this
        for(int x = 0; x < N; x++)
        {
            if(p == blocks[x].memAddr && blocks[x].freed == 0) // Valid free
            {
                real_free(p); // First, call the real free
                blocks[x].freed = 1; // Then, set block to freed state
                numFrees++;
                break;
            }
        }
    }
}

/*  postmain()
*   Called after main, used to print out the summary before program exit 
*   and perform relevant cleanup (printf buffer)
*/
void __attribute__((destructor)) postmain()
{
    // Cleanup printf buffer (if it is allocated)
    if(printf_buffer_addr != NULL)
    {
        free(printf_buffer_addr);
    }

    // Calculate the amount of memory leakage
    size_t leak_amount = 0;
    int leaked_blocks = 0;
    for(int x = 0; x < N; x++)
    {
        if(blocks[x].freed == 0) // Find the blocks that are still allocated
        {
            leak_amount += blocks[x].block_size;
            leaked_blocks++;
        }
    }
    
    //TODO: Finalize summary
    // Print Summary
    fprintf(stderr, "%s\n", pid);
    fprintf(stderr, "%s HEAP SUMMARY:\n", pid);
    fprintf(stderr, "%s   In use at program exit: %zu bytes in %d blocks\n", pid, leak_amount, leaked_blocks);
    fprintf(stderr, "%s   Total heap usage: %d allocs, %d frees, %zu bytes allocated\n", pid, numAllocs, numFrees, allocatedBytes);
    fprintf(stderr, "%s\n", pid);
    //TODO: explicitly list each memory loss and where it was in the program (stack trace)
    if(leak_amount == 0) // No leak
    {
        fprintf(stderr, "%s All memory blocks were freed -- no memory leak detected\n", pid);
    }
    else // Memory leak
    {
        fprintf(stderr, "%s !!LEAK DETECTED!!\n", pid);
        fprintf(stderr, "%s   lost: %zu bytes in %d blocks\n", pid, leak_amount, leaked_blocks);
    }
}
