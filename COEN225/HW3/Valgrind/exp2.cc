/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 2.2
*   11/1/22
*/
int main() {
    char *x = new char[10];
    x[9] = 'a'; //Fix - writing inside the array bounds now
    delete [] x; //Fix - freeing memory before program exit
    return 0;
}
/*
*   Errors:
*   Valgrind reports 2 errors. 1st error is an invalid write. 2nd error is a memory leak.
*   1st error is caused by going outside the bounds of the char array by attempting to 
*   write to the 10th index, but the array is from 0-9. The 2nd error is caused by not
*   freeing memory before the program exits.
*   
*   Fixes:
*   The fixes are straightforward. See the above code for the fixes.
*/