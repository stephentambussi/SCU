/*  
*   Stephen Tambussi
*   COEN225
*   Lecture 1
*   9/20/22
*/
#include <stdio.h>
#include <string.h>

int main(void)
{
    return 0;
}

/*
*   Basic C vulnerabilities
*   - strcpy does not observe memory boundary between variables --> overflow into neighboring variable
*   - Array indexing also does not observe mem boundary between neighboring variables --> overflow modifies neighbor variables
*   - Java and other high-level/newer languages prevent these vulnerabilities
*
*   Basic C++ vulnerabilities
*   - Provides SOME security improvements over C
*   - C++ will expand string variable for assignment to prevent overflow issue
*       - Still possible to cause overflow by using C strcpy & c string pointers
*   
*   Vulnerability: software/system security flaw
*   Exploit: payload that uses vulnerability
*/