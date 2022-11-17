#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
void foo()
{
  void *ptr = malloc(16);
  void *ptr2 = malloc(32);
  free(ptr);
  //free(ptr); //Not originally in test --> remove later
}
int main()
{
  void *ptr = malloc(16);
  foo();
}

/*  Valgrind output:
==2588== HEAP SUMMARY:
==2588==     in use at exit: 48 bytes in 2 blocks
==2588==   total heap usage: 3 allocs, 1 frees, 64 bytes allocated
==2588==
==2588== 16 bytes in 1 blocks are definitely lost in loss record 1 of 2
==2588==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2588==    by 0x804848C: main (test1.c:13)
==2588==
==2588== 32 bytes in 1 blocks are definitely lost in loss record 2 of 2
==2588==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2588==    by 0x804845A: foo (test1.c:7)
==2588==    by 0x8048497: main (test1.c:14)
==2588==
==2588== LEAK SUMMARY:
==2588==    definitely lost: 48 bytes in 2 blocks
==2588==    indirectly lost: 0 bytes in 0 blocks
==2588==      possibly lost: 0 bytes in 0 blocks
==2588==    still reachable: 0 bytes in 0 blocks
==2588==         suppressed: 0 bytes in 0 blocks
*/