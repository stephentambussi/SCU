#include <string.h>
#include <stdio.h>
int main()
{
    char formatstr[16];
    char str[16];
    
    printf("enter password:");
    scanf("%s",formatstr);
    scanf(formatstr,str);
}
/*
user@vm-coen225:~/class10$ flawfinder formatstr.c 
Flawfinder version 1.31, (C) 2001-2014 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 169
Examining formatstr.c

FINAL RESULTS:

formatstr.c:9:  [4] (buffer) scanf:
  The scanf() family's %s operation, without a limit specification, permits
  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a
  different input function.
formatstr.c:10:  [4] (buffer) scanf:
  The scanf() family's %s operation, without a limit specification, permits
  buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a
  different input function. If the scanf format is influenceable by an
  attacker, it's exploitable.
formatstr.c:5:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119:CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
formatstr.c:6:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119:CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.

ANALYSIS SUMMARY:

Hits = 4
Lines analyzed = 11 in approximately 0.01 seconds (1509 lines/second)
Physical Source Lines of Code (SLOC) = 10
Hits@level = [0]   0 [1]   0 [2]   2 [3]   0 [4]   2 [5]   0
Hits@level+ = [0+]   4 [1+]   4 [2+]   4 [3+]   2 [4+]   2 [5+]   0
Hits/KSLOC@level+ = [0+] 400 [1+] 400 [2+] 400 [3+] 200 [4+] 200 [5+]   0
Minimum risk level = 1
Not every hit is necessarily a security vulnerability.
There may be other security vulnerabilities; review your code!
See 'Secure Programming for Linux and Unix HOWTO'
(http://www.dwheeler.com/secure-programs) for more information.
*/