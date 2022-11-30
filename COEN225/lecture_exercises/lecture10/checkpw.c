#include <string.h>
#include <stdio.h>
char passwd[20]="california";
char input[16]="";
int matched=0;
int main()
{
    printf("enter password:");
    scanf("%s",input);

    if (strcmp(passwd,input) == 0)
        matched=1;

    if (matched)
        printf("you guessed right!\n");
    else
        printf("you guessed wrong!\n");
}
/*
user@vm-coen225:~$ flawfinder checkpw.c
Flawfinder version 1.31, (C) 2001-2014 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 169
Examining checkpw.c

FINAL RESULTS:

checkpw.c:10:  [4] (buffer) scanf:
  The scanf() family's %s operation, without a limit specification, permits
  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a
  different input function.
checkpw.c:3:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119:CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
checkpw.c:4:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119:CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.

ANALYSIS SUMMARY:

Hits = 3
Lines analyzed = 19 in approximately 0.01 seconds (2975 lines/second)
Physical Source Lines of Code (SLOC) = 16
Hits@level = [0]   0 [1]   0 [2]   2 [3]   0 [4]   1 [5]   0
Hits@level+ = [0+]   3 [1+]   3 [2+]   3 [3+]   1 [4+]   1 [5+]   0
Hits/KSLOC@level+ = [0+] 187.5 [1+] 187.5 [2+] 187.5 [3+] 62.5 [4+] 62.5 [5+]   0
Minimum risk level = 1
Not every hit is necessarily a security vulnerability.
There may be other security vulnerabilities; review your code!
See 'Secure Programming for Linux and Unix HOWTO'
(http://www.dwheeler.com/secure-programs) for more information.
*/