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
 * 
 *   NOTE:
 *      This program is a prototype and was only designed to work on the 5 tests.
 *      Running this program on code outside these tests may produce unexpected results.
 */

#define _GNU_SOURCE
#define N 50        // Max size of memory tracking array
#define DEBUG 0     // 0 = debug messages off | 1 = debug messages on

#include <execinfo.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// 'Linked list' to track allocated blocks
struct allocatedMem {
    size_t block_size;
    void *memAddr;          // Address that points to allocated block
    int freed;              // -1 = never used | 0 = still allocated | 1 = already freed 
    char stack_trace[4096]; // String to hold the stack trace
    int allocatorType;      // 0 = realloc | 1 = calloc | 2 = malloc
};

struct allocatedMem blocks[N]; // Array of structs (Linked List) to track allocated blocks
int lastUsed = 0;              // Keeps track of last allocated block index (for efficiency purposes)
int stackTraceIndex = 0;       // Holds the position of the node to print the stack trace to

// Global variables to keep track of total allocated mem, allocs, frees, and number of errors
int numAllocs = 0;
int numFrees = 0;
size_t allocatedBytes = 0;    // This keeps track of total heap usage, regardless of frees
int numErrors = 0;            // Invalid frees and memory leaks are counted as errors

// Misc. global variables
char pid_str[10];
int this_is_printf = 0;                     // This flag tells malloc that the calling function is printf
void *printf_buffer_addr = NULL;            // This tells the program the mem addr of the printf buffer for cleanup
static int recursively_called_malloc = 0;   // Flag specific to the malloc function to help with generate_stack_trace
static int recursively_called_calloc = 0;   // Flag specific to the calloc function to help with generate_stack_trace
static int recursively_called_free = 0;     // Flag specific to the free function to help with generate_stack_trace

/*  gdbout_parser()
*   Helper function to parse the output from running the gdb command
*/
void gdbout_parser(char *input_line, char *output_line)
{
    char line_copy[256];
    int line_num = 0;
    char *filename;
    char *address;
    char *func;

    // Get line number
    int digit = 0;
    for(int i = 0; i < strlen(input_line) - 1; i++)
    {
        if(isdigit(input_line[i]))
        {
            digit = input_line[i] - '0';
            line_num = line_num * 10 + digit;
        }
        if(input_line[i] == ' ' && input_line[i+1] == 'o')
            break;
    }

    // Get filename
    strcpy(line_copy, input_line); // Copy the string first since strtok modifies it
    filename = strtok(line_copy, "\"");
    filename = strtok(NULL, "\"");

    // Get address
    address = strstr(input_line, "0x");

    // Get function name
    func = strtok(input_line, "<");
    func = strtok(NULL, "+");

    sprintf(output_line, "%s   by %s: inside %s (%s on line %d)\n", pid_str, address, func, filename, line_num);
    if(DEBUG) fprintf(stderr, "++DEBUG++ %s\n", output_line);
}

/*  generate_stack_trace()
*   Generates trace at point of call and parses its contents into a
*   human-readable format
*/
void generate_stack_trace(char *tmpfile, char *backtracestr)
{
    if(DEBUG) fprintf(stderr, "++DEBUG++ Start of generate_stack_trace()\n");
    
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

    recursively_called_malloc = 1;
    recursively_called_calloc = 1;
    recursively_called_free = 1;

    size = backtrace(array, 10);
    backtrace_symbols_fd(array, size, f);   // This will write the backtrace to the tmpfile
    close(f);
    if(backtracestr) backtracestr[0] = 0;

    fp = fopen(tmpfile, "r");
    fclose(fopen("backtrace.gdbout", "w")); // This will zero the .gdbout file for each call to generate_stack_trace

    while(fgets(line, 256, fp))             // Parse the backtrace.txt file
    {
        char filename[10];
        char *offset;
        char system_str[100];
        // For simplicity, making assumption that executable name is always "a.out"
        if(strncmp(line, "./a.out", 7) == 0)
        {
            strcpy(filename, "a.out");
            offset = strtok(line, "[");
            offset = strtok(NULL, "]");
            snprintf(system_str, sizeof(system_str), "gdb -batch -ex 'file %s' -ex 'info line * %s' >> backtrace.gdbout", filename, offset);
            if(DEBUG) fprintf(stderr, "++DEBUG++ $ %s\n", system_str);
            system(system_str);
        }
        if(strncmp(line, "/lib/", 5) == 0)  // stop detector
        {
            break;
        }
    }
    fclose(fp);

    fp = fopen("backtrace.gdbout", "r");
    
    if(backtracestr == NULL)                // This is for malloc, calloc, and realloc
    {
        while(fgets(line, 256, fp))         // Parse the backtrace.gdbout file
        {
            char formatted_line[256];
            gdbout_parser(line, formatted_line);
            strcat(blocks[stackTraceIndex].stack_trace, formatted_line); // Append the formatted line to the block's stack trace string
        }
    }
    else // free() stack trace parsing
    {
        fprintf(stderr, "%s   at free\n", pid_str);
        while(fgets(line, 256, fp))
        {
            char formatted_line[256];
            gdbout_parser(line, formatted_line);
            strcat(backtracestr, formatted_line);   // Stack traces for invalid frees are printed when they occur, rather than in summary
        }
    }

    fclose(fp);

    recursively_called_malloc = 0;
    recursively_called_calloc = 0;
    recursively_called_free = 0;
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
        blocks[x].allocatorType = -1;
    }
    numAllocs = 0;
    numFrees = 0;
    allocatedBytes = 0;

    memset(pid_str, ' ', 10);
    sprintf(pid_str, "==%ld==", (long)getpid());
    
    fprintf(stderr, "%s A Memory Error Detector Program\n", pid_str);
    fprintf(stderr, "%s Created by Stephen Tambussi for COEN225\n", pid_str);
    fprintf(stderr, "%s\n", pid_str);

    unsetenv("LD_PRELOAD"); // Avoids fork bombing and enables system() to work correctly
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
    if (!recursively_called)    // Not recursively called
    {
        void *prev = ptr;       // Need to save ptr since realloc might mess with it behind the scenes
        recursively_called = 1;
        if (!real_realloc)
            real_realloc = dlsym(RTLD_NEXT, "realloc"); //set to real realloc function via dynamic linker (happens once due to static ptr)
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
                    blocks[lastUsed].allocatorType = 0;
                    stackTraceIndex = lastUsed;
                    numAllocs++;
                    allocatedBytes += new_size;

                    lastUsed++;
                }
                else
                {
                    fprintf(stderr, "##ERROR## program has reached the limit of memory tracking size --> INCREASE N\n");
                    recursively_called = 0;
                    return p;
                }
            }
            else // In this case, realloc allocates a new mem block, copies the data, and frees the old block
            {
                if(lastUsed < N)
                {
                    blocks[lastUsed].block_size = new_size;
                    blocks[lastUsed].memAddr = p;
                    blocks[lastUsed].freed = 0;
                    blocks[lastUsed].allocatorType = 0;
                    stackTraceIndex = lastUsed;
                    numAllocs++;
                    allocatedBytes += new_size;

                    lastUsed++;

                    for(int x = 0; x < N; x++) // Don't actually call free, since real_realloc already called it
                    {
                        if(prev == blocks[x].memAddr && blocks[x].freed == 1) // Invalid free
                        {
                            fprintf(stderr, "%s Invalid free: free(%p)\n", pid_str, p);
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
                    recursively_called = 0;
                    return p;
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
                    stackTraceIndex = x;

                    allocatedBytes += new_size;
                    numAllocs++;
                    flag = 1;
                    break;
                }
            }
            if(flag == 0) // If the loop finished without matching any address
            {
                // Program is attempting to realloc with invalid address
                fprintf(stderr, "%s Invalid address with realloc(): %p\n", pid_str, p);
            }
        }

        generate_stack_trace("backtrace.txt", NULL);

        recursively_called = 0;
    }
    else // Recursively called
    {
        if (!real_realloc)
            real_realloc = dlsym(RTLD_NEXT, "realloc"); // To ensure that real realloc function is assigned before calling
        
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
    static void *(*real_calloc)(size_t, size_t) = NULL;
    void *p;
    if (!recursively_called_calloc) // Not recursively called
    {
        recursively_called_calloc = 1;
        if (!real_calloc)
            real_calloc = dlsym(RTLD_NEXT, "calloc"); //set to real calloc function via dynamic linker (happens once due to static ptr)
        p = real_calloc(num, size);

        if(DEBUG) fprintf(stderr, "++DEBUG++ %p = calloc(%zu, %zu) called inside if\n", p, num, size);

        if(lastUsed < N)
        {
            blocks[lastUsed].block_size = num * size; // This is the primary difference between malloc
            blocks[lastUsed].memAddr = p;
            blocks[lastUsed].freed = 0;
            blocks[lastUsed].allocatorType = 1;
            stackTraceIndex = lastUsed;

            numAllocs++;
            allocatedBytes += num * size;
            lastUsed++;
        }
        else
        {
            fprintf(stderr, "##ERROR## program has reached the limit of memory tracking size --> INCREASE N\n");
            recursively_called_calloc = 0;
            return p;
        }

        generate_stack_trace("backtrace.txt", NULL);

        recursively_called_calloc = 0;
    }
    else // Recursively called or called to avoid memory tracking functions
    {
        if (!real_calloc)
            real_calloc = dlsym(RTLD_NEXT, "calloc");
        
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
    static void *(*real_malloc)(size_t) = NULL;
    void *p;
    int f;
    if (!recursively_called_malloc) // Not recursively called
    {
        recursively_called_malloc = 1;
        if (!real_malloc)
            real_malloc = dlsym(RTLD_NEXT, "malloc"); //set to real malloc function via dynamic linker (happens once due to static ptr)
        p = real_malloc(size);

        if(DEBUG) fprintf(stderr, "++DEBUG++ %p = malloc(%zu) called inside if\n", p, size);

        if(lastUsed < N)
        {
            blocks[lastUsed].block_size = size;
            blocks[lastUsed].memAddr = p;
            blocks[lastUsed].freed = 0;
            blocks[lastUsed].allocatorType = 2;
            allocatedBytes += size;
            // Set printf_buffer_index so destructor can free the printf buffer
            if(this_is_printf) printf_buffer_addr = p;
            stackTraceIndex = lastUsed;
            numAllocs++;

            lastUsed++;
        }
        else
        {
            fprintf(stderr, "##ERROR## program has reached the limit of memory tracking size --> INCREASE N\n");
            recursively_called_malloc = 0;
            return p;
        }

        if(!this_is_printf) generate_stack_trace("backtrace.txt", NULL); // Don't call stack trace on printf buffer malloc

        recursively_called_malloc = 0;
    }
    else // Recursively called or called to avoid memory tracking functions
    {
        if (!real_malloc)
            real_malloc = dlsym(RTLD_NEXT, "malloc");
        
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
    static void (*real_free)(void *) = NULL;
    char backtracestr[4096];
    if (!recursively_called_free) // Not recursively called
    {
        recursively_called_free = 1;
        if (!real_free)
            real_free = dlsym(RTLD_NEXT, "free"); //set to real free function via dynamic linker (happens once due to static ptr) 

        if(DEBUG) fprintf(stderr, "++DEBUG++ free(%p) called inside if\n", p);

        int flag = 0;
        for(int x = 0; x < N; x++)
        {
            if(p == blocks[x].memAddr && blocks[x].freed == 1) // Invalid free --> double free/free-after-free
            {
                fprintf(stderr, "%s Invalid free() - memory was already freed at %p\n", pid_str, p);
                numFrees++;
                numErrors++;
                flag = 1;
                if(p != printf_buffer_addr) 
                {
                    generate_stack_trace("backtrace.txt", backtracestr); // Don't call stack trace on printf buffer free
                    fprintf(stderr, "%s", backtracestr);
                    fprintf(stderr, "%s\n", pid_str);
                }
                break;
            }
            else if(p == blocks[x].memAddr && blocks[x].freed == 0) // Valid free
            {
                real_free(p);           // First, call the real free
                blocks[x].freed = 1;    // Then, set block to freed state
                numFrees++;
                flag = 1;
                break;
            }
        }

        if(flag == 0) // If the loop finished without matching any address
        {
            // Program is attempting to free with invalid address or
            // on memory that was never allocated before
            fprintf(stderr, "%s Invalid free() - bad address: %p\n", pid_str, p);
            numFrees++;
            numErrors++;
            if(p != printf_buffer_addr) 
            {
                generate_stack_trace("backtrace.txt", backtracestr);
                fprintf(stderr, "%s", backtracestr);
                fprintf(stderr, "%s\n", pid_str);
            }
        }
        
        recursively_called_free = 0;
    }
    else // Recursively called or called to avoid memory tracking functions
    {
        if (!real_free)
            real_free = dlsym(RTLD_NEXT, "free");
        
        if(DEBUG) fprintf(stderr, "++DEBUG++ free(%p) called inside else\n", p);
        
        for(int x = 0; x < N; x++)
        {
            if(p == blocks[x].memAddr && blocks[x].freed == 0) // Valid free
            {
                real_free(p);           // First, call the real free
                blocks[x].freed = 1;    // Then, set block to freed state
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
            numErrors++;
        }
    }
    
    // Print Summary
    fprintf(stderr, "%s\n", pid_str);
    fprintf(stderr, "%s HEAP SUMMARY:\n", pid_str);
    fprintf(stderr, "%s   In use at program exit: %zu bytes in %d blocks\n", pid_str, leak_amount, leaked_blocks);
    fprintf(stderr, "%s   Total heap usage: %d allocs, %d frees, %zu bytes allocated\n", pid_str, numAllocs, numFrees, allocatedBytes);
    fprintf(stderr, "%s\n", pid_str);

    if(leak_amount == 0) // No leak
    {
        fprintf(stderr, "%s All memory blocks were freed -- no memory leak detected\n", pid_str);
    }
    else // Memory leak
    {
        fprintf(stderr, "%s !!LEAK DETECTED!!\n", pid_str);
        fprintf(stderr, "%s\n", pid_str);
        fprintf(stderr, "%s TRACE\n", pid_str);
        fprintf(stderr, "%s =====================================================\n", pid_str);
        for(int x = 0; x < N; x++)
        {
            if(blocks[x].freed == 0)
            {
                char allocator[10];
                if(blocks[x].allocatorType == 0) // realloc
                    strcpy(allocator, "realloc");
                else if(blocks[x].allocatorType == 1) // calloc
                    strcpy(allocator, "calloc");
                else if(blocks[x].allocatorType == 2) // malloc
                    strcpy(allocator, "malloc");

                fprintf(stderr, "%s %zu bytes lost in a block\n", pid_str, blocks[x].block_size);
                fprintf(stderr, "%s   at %s\n", pid_str, allocator);
                fprintf(stderr, "%s", blocks[x].stack_trace);
                fprintf(stderr, "%s\n", pid_str);
            }
        }
        fprintf(stderr, "%s =====================================================\n", pid_str);
        fprintf(stderr, "%s\n", pid_str);
        fprintf(stderr, "%s LEAK SUMMARY\n", pid_str);
        fprintf(stderr, "%s   lost: %zu bytes in %d blocks\n", pid_str, leak_amount, leaked_blocks);
    }
    fprintf(stderr, "%s\n", pid_str);
    fprintf(stderr, "%s ERROR SUMMARY: %d errors found in target process\n", pid_str, numErrors);
}
