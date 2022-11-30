
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    char line[256];
    int flist[8];
    int flck[8];
    int i=0;
    struct thread_resource *current;
    while (printf("enter file to open$ "), fgets (line, 255, stdin)!=NULL) {
        line[strlen(line)-1] = '\0';
        printf("%s",line);
        printf("\n");
        flist[i]=open(line,O_RDWR|O_EXCL);
        flck[i]=flock(flist[i], LOCK_EX);
        printf("open status=%d\n",flist[i]);
        printf("lock status=%d\n",flck[i]);
        i++;
    }
    return 0;
}
/*
user@vm-coen225:~$ flawfinder class8/FileLockingApp.c
Flawfinder version 1.31, (C) 2001-2014 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 169
Examining class8/FileLockingApp.c

FINAL RESULTS:

class8/FileLockingApp.c:9:  [2] (buffer) char:
  Statically-sized arrays can be improperly restricted, leading to potential
  overflows or other issues (CWE-119:CWE-120). Perform bounds checking, use
  functions that limit length, or ensure that the size is larger than the
  maximum possible length.
class8/FileLockingApp.c:18:  [2] (misc) open:
  Check when opening files - can an attacker redirect it (via symlinks),
  force the opening of special file type (e.g., device files), move things
  around to create a race condition, control its ancestors, or change its
  contents? (CWE-362).
class8/FileLockingApp.c:15:  [1] (buffer) strlen:
  Does not handle strings that are not \0-terminated; if given one it may
  perform an over-read (it could cause a crash if unprotected) (CWE-126).

ANALYSIS SUMMARY:

Hits = 3
Lines analyzed = 25 in approximately 0.01 seconds (3691 lines/second)
Physical Source Lines of Code (SLOC) = 25
Hits@level = [0]   0 [1]   1 [2]   2 [3]   0 [4]   0 [5]   0
Hits@level+ = [0+]   3 [1+]   3 [2+]   2 [3+]   0 [4+]   0 [5+]   0
Hits/KSLOC@level+ = [0+] 120 [1+] 120 [2+]  80 [3+]   0 [4+]   0 [5+]   0
Minimum risk level = 1
Not every hit is necessarily a security vulnerability.
There may be other security vulnerabilities; review your code!
See 'Secure Programming for Linux and Unix HOWTO'
(http://www.dwheeler.com/secure-programs) for more information.
user@vm-coen225:~$ 
*/