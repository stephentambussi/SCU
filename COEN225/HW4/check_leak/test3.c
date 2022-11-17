#include <stdio.h>
#include <stdlib.h>

int main () {
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "tutorialspoint");
   printf("String = %s,  Address = %u\n", str, str);

   /* Reallocating memory */
   str = (char *) realloc(str, 25);
   strcat(str, ".com");
   printf("String = %s,  Address = %u\n", str, str);

   return(0);
}

/*  Valgrind output:
==2601== HEAP SUMMARY:
==2601==     in use at exit: 25 bytes in 1 blocks
==2601==   total heap usage: 3 allocs, 2 frees, 1,064 bytes allocated
==2601==
==2601== 25 bytes in 1 blocks are definitely lost in loss record 1 of 1
==2601==    at 0x402F2CC: realloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2601==    by 0x80484E0: main (test3.c:13)
==2601==
==2601== LEAK SUMMARY:
==2601==    definitely lost: 25 bytes in 1 blocks
==2601==    indirectly lost: 0 bytes in 0 blocks
==2601==      possibly lost: 0 bytes in 0 blocks
==2601==    still reachable: 0 bytes in 0 blocks
==2601==         suppressed: 0 bytes in 0 blocks
*/