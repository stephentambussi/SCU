#include <stdio.h>
#include <string.h>
int main(void) {
  int num1 = 0x7fffffff;
  int num2 = 0x1;
  int addition_result = num1 + num2;
  printf ("%d\n", addition_result);
    
  unsigned int num3 = 0xffffffff;
  unsigned int num4 = 0x1;
  unsigned int uaddition_result = num3 + num4;
  printf ("%u\n", uaddition_result);
    
  printf ("%d\n", num1+num4);
  printf ("%d\n", -2147483648);
  printf ("%d\n", 2147483648);
  printf ("%u\n", num1+num4);
  return 0;
}