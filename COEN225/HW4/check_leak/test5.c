#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
void foo()
{
  void *ptr = malloc(16);
  void *ptr2 = malloc(32);
  free(ptr);
  free(ptr);
}
int main()
{
  void *ptr = malloc(16);
  foo();
}

/*  Valgrind output:
==2613== Invalid free() / delete / delete[] / realloc()
==2613==    at 0x402E358: free (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2613==    by 0x8048479: foo (test5.c:9)
==2613==    by 0x80484A5: main (test5.c:14)
==2613==  Address 0x41f9068 is 0 bytes inside a block of size 16 free'd
==2613==    at 0x402E358: free (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2613==    by 0x804846B: foo (test5.c:8)
==2613==    by 0x80484A5: main (test5.c:14)
==2613==  Block was alloc'd at
==2613==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2613==    by 0x804844A: foo (test5.c:6)
==2613==    by 0x80484A5: main (test5.c:14)
==2613==
==2613==
==2613== HEAP SUMMARY:
==2613==     in use at exit: 48 bytes in 2 blocks
==2613==   total heap usage: 3 allocs, 2 frees, 64 bytes allocated
==2613==
==2613== 16 bytes in 1 blocks are definitely lost in loss record 1 of 2
==2613==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2613==    by 0x804849A: main (test5.c:13)
==2613==
==2613== 32 bytes in 1 blocks are definitely lost in loss record 2 of 2
==2613==    at 0x402D17C: malloc (in /usr/lib/valgrind/vgpreload_memcheck-x86-linux.so)
==2613==    by 0x804845A: foo (test5.c:7)
==2613==    by 0x80484A5: main (test5.c:14)
==2613==
==2613== LEAK SUMMARY:
==2613==    definitely lost: 48 bytes in 2 blocks
==2613==    indirectly lost: 0 bytes in 0 blocks
==2613==      possibly lost: 0 bytes in 0 blocks
==2613==    still reachable: 0 bytes in 0 blocks
==2613==         suppressed: 0 bytes in 0 blocks
*/