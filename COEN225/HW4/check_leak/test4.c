#include <stdio.h>
int main() {
        int i, * ptr, sum;
        sum = 0;
        ptr = calloc(10, sizeof(int));
        if (ptr == NULL) {
            printf("Error! memory not allocated.");
            exit(0);
        }
        printf("Building and calculating the sequence sum of the first 10 terms \n ");
        for (i = 0; i < 10; ++i) { * (ptr + i) = i;
            sum += * (ptr + i);
        }
        printf("Sum = %d", sum);

        sum = 0;
        ptr = calloc(10, sizeof(int));
        if (ptr == NULL) {
            printf("Error! memory not allocated.");
            exit(0);
        }
        printf("Building and calculating the sequence sum of the first 10 terms \n ");
        for (i = 0; i < 10; ++i) { * (ptr + i) = i;
            sum += * (ptr + i);
        }
        printf("Sum = %d", sum);

        free(ptr);
        return 0;
}

/*  Valgrind output:
==2607== HEAP SUMMARY:
==2607==     in use at exit: 40 bytes in 1 blocks
==2607==   total heap usage: 3 allocs, 2 frees, 1,104 bytes allocated
==2607==
==2607== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==2607==    at 0x402F0B8: calloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2607==    by 0x80484BE: main (test4.c:5)
==2607==
==2607== LEAK SUMMARY:
==2607==    definitely lost: 40 bytes in 1 blocks
==2607==    indirectly lost: 0 bytes in 0 blocks
==2607==      possibly lost: 0 bytes in 0 blocks
==2607==    still reachable: 0 bytes in 0 blocks
==2607==         suppressed: 0 bytes in 0 blocks
*/