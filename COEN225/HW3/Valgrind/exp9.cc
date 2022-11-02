/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 2.9
*   11/1/22
*/
void dispose(long double *p) {
    delete[] p;
}

int main() {
    long double *a = new long double [10];
    long double *b = a; //Fix - use b to de-allocate the array instead
    a+=3;
    dispose(b);
    return 0;
}
/*
*   Error:
*   Valgrind reports 1 error. There is a memory leak due to an invalid delete call. The delete call
*   is invalid because immediately before it is called, the ptr to the array of long doubles is
*   incremented to instead be pointing to 3 blocks after the first block of the array. For the 
*   delete call to work correctly, it must be passed a ptr that points to the first block of
*   the allocated memory.
*
*   Fix:
*   There are a few methods to resolve this issue. The easiest way is to simply comment out the
*   offending line "a+=3". However, if the program behavior is wished to be maintained, then 
*   a better solution is to have another ptr variable point to the first block of allocated
*   memory and use that to de-allocate the array when ready. This solution is shown above.
*/