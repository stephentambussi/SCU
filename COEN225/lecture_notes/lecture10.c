/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 10
*   11/29/22
*/
#include <stdio.h>
#include <string.h>

int main()
{
    return 0;
}

/*
*   TODO: review Shellshock exploit video
*
*   SECURE CODING TOOLS FOR C/C++
*       Dynamic                 Static
*       /     \                 /    \
*      V       V               V      V
*   Dynamic   Fuzzing     Static     Composition
*   Analysis              Analysis   Analysis
*
*   Dynamic analysis examples: valgrind, fuzzing
*   Static analysis examples: gcc (includes tool)
*
*   Valgrind alternative: Google Sanitizer for C/C++
*       valgrind shortcomings: slow, resources demanding, cannot detect
*                              global/local variable overflow
*
*       Errors that Google Sanitizer can detect that Valgrind CANT
*           Global/local variable overflow detection:
*           $ gcc checkpw.c -fsanitize=address
*
*           Stack Space After Return Detection:
*           $ gcc StackUseAfterReturn.c -fsanitize=address
*           $ ASAN_OPTIONS=detect_stack_use_after_return=1 ./a.out
*
*   Static Analysis
*       Definition: static analysis is the automated analysis of source code for
*                   bugs/vulnerabilities without executing the application.
*       Static vs. Dynamic Analysis
*           - Static analysis is done at development phase
*           - Dynamic analysis is done at testing phase
*           6 phases of software development life cycle:
*               analysis->design->development->testing->deployment->maintenance
*           
*           Dynamic analysis challenge: too slow, too resource demanding
*           Static analysis challenge: false positives, false negatives (not able to find real flaws)
*
*       Static analysis areas:
*           Vulnerable Strings/Patterns/Functions Matching
*           Data Flow Analysis
*           Control Flow Analysis
*           Taint Analysis
*           
*       Strings/Patterns/Functions Matching Static Analysis: Flawfinder
*           Buffer overflow: checkpw.c
*           Format string:   formatstr.c
*           File I/O:        demo_open.c, demo_chown.c
*       
*       Weak/Obsolete Function Detection: Coverity
*           MD5 (128 bits) is a weak hash function and easily defeated with modern computers
*           Coverity can detect weak hash functions
*       
*       Data Flow Analysis: Coverity and Java Compiler
*           Detecting areas: uninitialized variables
*           Uninit.java, Uninit2.java, Uninit3.java
*
*       Control Flow Analysis: Coverity and Java Compiler
*           Detecting areas: unreachable/dead code
*           Deadcode.java
*
*       Taint Analysis
*           Taint-style vulnerability is unchecked input data reaching a sensitive sink (output destination). 
*           The unchecked input can be crafted by an attacker to exploit the sink operation.
*           SEE VIDEO
*           CallGDB4result.c
*
*   Composition Analysis
*       Software composition analysis (SCA) is an automated process that identifies the open source software in a codebase. 
*       This analysis is performed to evaluate security, license compliance, and code quality. 
*       Companies need to be aware of open source license limitations and obligations.
*
*       In modern commercial software development, up to 90% of code come from open source libraries.
*       It is important to test such libraries, in addition to a company's own code.
*/