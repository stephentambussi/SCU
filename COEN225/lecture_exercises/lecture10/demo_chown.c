#define _POSIX_SOURCE
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#undef _POSIX_SOURCE
#include <stdio.h>

int main() {
    char fn[]="./temp.file";
    FILE *stream;
    struct stat info;

    if ((stream = fopen(fn, "w")) == NULL)
        perror("fopen() error");
    else {
        fclose(stream);
        stat(fn, &info);
        printf("original owner was %d and group was %d\n", info.st_uid,
                info.st_gid);
        if (chown(fn, 25, 0) != 0)
            perror("chown() error");
        else {
            stat(fn, &info);
            printf("after chown(), owner is %d and group is %d\n",
                    info.st_uid, info.st_gid);
        }
        unlink(fn);
    }
}
/*
user@vm-coen225:~/class10$ flawfinder demo_chown.c
Flawfinder version 1.31, (C) 2001-2014 David A. Wheeler.
Number of rules (primarily dangerous function names) in C/C++ ruleset: 169
Examining demo_chown.c

FINAL RESULTS:

demo_chown.c:20:  [5] (race) chown:
  This accepts filename arguments; if an attacker can move those files, a
  race condition results. (CWE-362). Use fchown( ) instead.
demo_chown.c:13:  [2] (misc) fopen:
  Check when opening files - can an attacker redirect it (via symlinks),
  force the opening of special file type (e.g., device files), move things
  around to create a race condition, control its ancestors, or change its
  contents? (CWE-362).

ANALYSIS SUMMARY:

Hits = 2
Lines analyzed = 29 in approximately 0.01 seconds (4032 lines/second)
Physical Source Lines of Code (SLOC) = 27
Hits@level = [0]   0 [1]   0 [2]   1 [3]   0 [4]   0 [5]   1
Hits@level+ = [0+]   2 [1+]   2 [2+]   2 [3+]   1 [4+]   1 [5+]   1
Hits/KSLOC@level+ = [0+] 74.0741 [1+] 74.0741 [2+] 74.0741 [3+] 37.037 [4+] 37.037 [5+] 37.037
Minimum risk level = 1
Not every hit is necessarily a security vulnerability.
There may be other security vulnerabilities; review your code!
See 'Secure Programming for Linux and Unix HOWTO'
(http://www.dwheeler.com/secure-programs) for more information.
*/