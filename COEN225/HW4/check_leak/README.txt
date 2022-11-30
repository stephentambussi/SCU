Stephen Tambussi
COEN225 - HW4: Memory Leak Detector
11/29/22
Summary of Implementation

My implementation not only incorporates accurate memory tracking on the target process,
but also provides stack traces for invalid frees and memory leaks, similar to valgrind.

    The memory tracking is performed through the intercepted memory allocation functions:
    malloc, calloc, realloc, and free. Each of these functions track memory by updating
    the global "linked list". I say linked list in quotes because the data structure is 
    not truly a linked list, but rather an array of structs with a fixed size. Each node
    of the list has 5 member variables:
        block_size      - amount of memory allocated
        memAddr         - holds address to allocated block
        freed           - state variable that indicates if block was freed or not
        stack_trace     - string that holds the stack trace of the allocation call
        allocatorType   - indicator to determine which function allocated this block
    Furthermore, there are multiple global variables which keep track of the number of
    allocations, number of frees, number of errors, and total amount of allocated bytes.
    There is also a global variable for tracking the index of the next free block in the list. 
    The functions realloc, calloc, and malloc each increment this variable when allocating 
    a new chunk of memory.

    Stack traces are provided for memory leaks and invalid frees. For memory leaks,
    stack traces are displayed in the leak summary section, like in valgrind. Each point in
    the program where a leak was detected has an associated stack trace to help the user
    debug their code. Stack traces for invalid frees are printed when they occur, rather 
    than in the leak summary section.
    In every function, a call to generate_stack_trace is made each time the function is called 
    and the returned string is saved to the block's stack_trace field. The generate_stack_trace
    function works in the following way:
        1) generate raw stack trace data at point of call
        2) save this raw data to a temp file
        3) parse this temp file, extracting data such as executable name and addresses
        4) use this data to call gdb through system() to get filename, line num, and functions
        5) write gdb output to another temp file
        6) parse this temp file to create formatted string for human-readable stack trace
            - the function gdbout_parser does this
        7) append these formatted strings to the block's stack_trace variable
    For invalid frees, the stack trace is printed out immediately after the call to 
    generate_stack_trace. For memory leaks, the linked list is scanned in the postmain function
    to determine which allocations caused leaks and need their trace printed out. Only allocs that
    caused leaks have their stack traces displayed.

    One last important point, my implementation also intercepts the printf function. Due to the way
    printf works, it would allocate a buffer and then skew my memory tracking functions. I noticed
    the non-intercepted version of printf would allocate memory, but then not free it (at least explicitly). 
    To resolve this, I intercepted printf calls in the target program and made one small change. 
    This intercepted printf frees its malloc'd buffer in the postmain function. After this fix, the 
    output from my implementation matches the output of valgrind.
