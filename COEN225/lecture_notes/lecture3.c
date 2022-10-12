/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 3
*   10/4/22
*/
#include <stdio.h>
#include <string.h>

int main(void)
{
    return 0;
}

/*
*   Stack Frame Canary:
*       [local variables..........][ebp base register][return addr][parameters..........]
*           |                                  
*           V
*       [local variables..........][CANARY][ebp base register][return addr][parameters..........]
*   - Added to binaries to protect the return pointer against buffer overflow attacks
*       - If incorrect canary is detected during certain execution stages (right before return) --> program terminated
*   - Does not protect against string buffer overflow exploit as that modifies local variables only
*
*   ASLR (address space layout randomization)
*   - Guards against buffer-overflow attacks by randomizing mem addresses for running processes
*       - Makes the addresses not predictable
*
*   Pointer Subterfuge
*   -------------------------------
*   C Function Pointer Overwrite
*   - Similar to string buffer overflow, overwrite the value of pointer to change the function that is executed
*       - Function pointers are seldom used though so not very practical
*
*   C++ Virtual Pointer & Virtual Table (Basic Overview)
*   - Virtual table: lookup table of virtual function pointers --> one entry for each virtual function that can be called
*                    by objects of the class
*       - Every class that uses virtual functions (or is derived from class that uses them) is given its own virtual table
*   - Virtual function: member function that is declared in base class and redefined by a derived class
*
*   C++ Virtual Table Exploit
*   - Stealing virtual pointers to have functions from another derived class (still sharing same parent class)
*     operate on specified derived class instead
*
*   Global Offset Table (GOT) Overview
*   - Section of program's memory that holds addresses of functions that are dynamically linked
*       - Library functions are not mapped to their actual code until they are first called
*   - PLT (Procedure Linkage Table): responsible for calling the dynamic linker with the function name that should be resolved
*
*   GOT Exploit
*   - Similar to string buffer overflow, overwrite an instruction's linked address to something like execve to run a shell
*
*/