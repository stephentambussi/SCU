/*
 * Given a program with runtime vulnerabilities, indicate which ones can/cannot be detected by Valgrind/Google Sanitizer.
 */
#include <string.h>
#include <stdio.h>

int *f()
{
  int i = 42;
  int *p = &i;
  return p;
}

/*  GLOBAL VARIABLE OVERFLOW - GS=Yes | Valgrind=No  */
char passwd[20] = "california";
char input[16] = "";
int matched = 0;
int main(int argc, char **argv)
{
  printf("enter password:");
  scanf("%s", input);

  if (strcmp(passwd, input) == 0)
    matched = 1;

  if (matched)
    printf("you guessed right!\n");
  else
    printf("you guessed wrong!\n");

/*  UNINITIALIZED MEMORY - GS=Yes | Valgrind=Yes  */
  int a[2];
  int b = a[0];

/*  STACK USE AFTER RETURN - GS=Yes | Valgrind=No  */
  int *c = f();

/*  UNDEFINED BEHAVIOR - GS=Yes | Valgrind=No  */
  int d = 0x7fffffff + argc;

/*  MEMORY LEAKS - GS=Yes | Valgrind=Yes  */
  void *p = malloc(10);

/*  DATA RACES - GS=Yes | Valgrind=Yes(Helgrind)  */
  //See any multi-threaded program without mutex lock for critical sections

  return 0;
}
/*        Comparison between Valgrind and Google Sanitizer
 * Vulnerability:                Google Sanitizer    Valgrind
 * Var overflow (local, global)    Caught            *Missed*
 * Uninitialized memory            Caught            Caught
 * Stack use after return          Caught            *Missed*
 * Undefined behavior              Caught            *Missed*
 * Memory leaks                    Caught            Caught
 * Data races                      Caught            Helgrind
 */