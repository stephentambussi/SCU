/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 2.8
*   11/1/22
*/
#include <cstdlib>			// for free()

void dispose(double *ptr) {
    //free(ptr);
    delete [] ptr;
}

int main() {
    double *p = new double[1000];
    dispose(p);
    return 0;
}
/*
*   Error:
*   Valgrind reports 1 error. In this case, the free() function should not be used for
*   de-allocating memory that was allocated using new. 
*
*   Fix:
*   To fix this bug, the free() statement was changed to a delete [] statement as
*   seen above.
*/