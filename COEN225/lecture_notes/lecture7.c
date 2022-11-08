/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 7
*   11/1/22
*/
#include <stdio.h>
#include <string.h>

/*
*   Homework 4 Discussion
*   -----------------------------------------
*   Dissecting GCC
*   - compiling with -v (verbose) flag will produce useful information about the compilation process
*   - gcc is not really the compiler itself, rather it is a driver for the c compiler
*       - "cc1" is the compiler and it converts the .c file to an assembly file (.s)
*       - then, the assembler will convert the .s file into .o file
*       - finally, the linker "collect2" will fill the unresolved function addresses
*         and make the program executable
*   - can pass gcc a flag to only run one or some of the compiler steps
*       - For example: "gcc -S mainfoobar.c" will only execute the compilation process and return
*         mainfoobar.s
*       - Another example: "gcc -c mainfoobar.c" will return object code as mainfoobar.o
*   - Divide a single program into multiple programs to enable concurrent development:
*       NOTE: this is an example of static linking
*       mainfoobar.c --> main.c | foo.c | bar.c
*/                          
        // MAIN.C
        extern int foo(); //need extern keyword since foo is in another file
        int main() {
            int x=1;
            x = foo();    
        }
        // FOO.C
        extern int bar(); //need extern keyword since bar is in another file
        int foo() {
            int y = 2;
            y = bar();
            return y;
        }
        // BAR.C
        int bar() {
            printf("bar here\n");
            return 0;
        }
/*
*       Compile each of the above programs to get their object code:
*           gcc -c main.c
*           gcc -c foo.c
*           gcc -c bar.c
*       Link them together:
*           gcc main.o foo.o bar.o
*       
*   Shared/Dynamic Linking vs Static Linking
*       Static linking: linking object code with its function addresses before the program is run
*       Dynamic linking: dynamic library that is shared by all processes on a machine
*           Example library: libc.so (upgrading libc.so does not require re-compilation of applications)
*           Example to create library: gcc -g -shared -fPIC foo.c bar.c -o foobar.so
*               - foo.c and bar.c are going to be created into a shared library called foobar.so
*               - "shared" is used to indicate that this library can be shared across programs
*               - "PIC" = position-independent-code meaning that the library can be placed anywhere
*                  in memory
*               - ".so" stands for shared object
*               Then: "gcc main.o foobar.so" to link the shared library with object code of main
*        
*/