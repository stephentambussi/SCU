#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    fprintf(stderr, "malloc some memory!\n");

    void *ptr1 = malloc(1024);
    fprintf(stderr, "ptr1: %p\n", ptr1);

    if (!ptr1)
        fprintf(stderr, "handle ptr1 error\n");

    void *ptr2 = malloc(28);
    fprintf(stderr, "ptr2: %p\n", ptr2);

    if (!ptr2)
        fprintf(stderr, "handle ptr2 error\n");


    free(ptr1);
    free(ptr2);

    return 0;
}

/*  Valgrind output:
==2595== HEAP SUMMARY:
==2595==     in use at exit: 0 bytes in 0 blocks
==2595==   total heap usage: 2 allocs, 2 frees, 1,052 bytes allocated
==2595==
==2595== All heap blocks were freed -- no leaks are possible
*/