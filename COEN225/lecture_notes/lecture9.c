/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 9
*   11/15/22
*/
#include <stdio.h>
#include <string.h>

int main()
{
    return 0;
}

/*
*   TODO: do study questions for final from this lecture
*
*   Deadlocks
*   - see deadlock.c
*   - Helgrind CANNOT usually detect deadlocks (still a good idea to try it)
*       $ valgrind --tool=helgrind ./a.out
*   - detecting deadlocks on linux processes
*       - See video and answer study questions
*
*   Fuzzing
*   - an automated software testing technique that involves providing invalid,
*     unexpected, or random data as inputs to a computer program
*
*     AFL (American Fuzzy Lop): security-oriented fuzzer that employs compile-time instrumentation 
*                               and mutating algorithms to automatically discover test cases that
*                               trigger new internal states in the targeted application.
*/