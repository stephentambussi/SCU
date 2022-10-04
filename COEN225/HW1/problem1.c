/*  
*   Stephen Tambussi
*   COEN225
*   HW1: problem 1
*   10/4/22
*/
#include <stdio.h>
#include <string.h>
int a1[5];
int a4[9][9];
int main()
{
    // using printf format %p to print the address
    printf("a1 %p\n",&a1[0]);
    printf("a4 %p\n",&a4[0][0]);
    int start_idx = (&a4[0][0] - &a1[0]);
    printf("%d \n", start_idx);
    a1[0]=9;
    // index of a1 that starts at mem addr for a4 = 8
    a1[8]=9;  a1[16]=9; //row 1
    a1[18]=9; a1[24]=9; //row 2
    a1[28]=9; a1[32]=9; //row 3
    a1[38]=9; a1[40]=9; //row 4
    a1[48]=9;           //row 5
    a1[56]=9; a1[58]=9; //row 6
    a1[64]=9; a1[68]=9; //row 7
    a1[72]=9; a1[78]=9; //row 8
    a1[80]=9; a1[88]=9; //row 9
    printf("a1[]=%d,%d,%d,%d,%d\n",a1[0],a1[1],a1[2],a1[3],a1[4]);
    printf("a4[]=\n");
    for (int i=0; i<9; i++) 
    {
        for (int j=0; j<9; j++)
            printf("%d,",a4[i][j]);
        printf("\n");
    }
    /*  
    *   Desired output for a4:
    *   9,0,0,0,0,0,0,0,9,
    *   0,9,0,0,0,0,0,9,0,
    *   0,0,9,0,0,0,9,0,0,
    *   0,0,0,9,0,9,0,0,0,
    *   0,0,0,0,9,0,0,0,0,
    *   0,0,0,9,0,9,0,0,0,
    *   0,0,9,0,0,0,9,0,0,
    *   0,9,0,0,0,0,0,9,0,
    *   9,0,0,0,0,0,0,0,9, 80,88
    */
    return 0;
}
/*  Solution:
*   The first thing I did was to calculate the difference in the memory address between a1 and a4.
*   This value turned out to be 32 bytes. Knowing this, it was trivial to determine the index of a1
*   that would begin to modify the next consecutive block of memory (a4). Since ints are 4 bytes on
*   most systems, you divide the mem addr difference by 4: 32 / 4 = 8. This result gives you the
*   index of a1 that will overflow the first block of memory for a4. Thus, you can modify a4
*   through a1 starting at index 8.
*/
