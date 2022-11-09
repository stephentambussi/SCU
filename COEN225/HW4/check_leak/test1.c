#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
void foo()
{
  void *ptr = malloc(16);
  void *ptr2 = malloc(32);
  free(ptr);
}
int main()
{
  void *ptr = malloc(16);
  foo();
}
