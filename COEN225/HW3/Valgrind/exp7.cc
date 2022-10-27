/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 2.7
*   11/1/22
*/
int main() {
    double *p = new double[1000];
    delete [] p; //This is the fix
    return 0;
}
/*
*   Error:
*   Valgrind reports 1 error. The delete statement is incorrect to free memory for allocated
*   arrays.
*
*   Fix:
*   To fix the bug, the delete statement needs to be "delete [] p" as seen above.
*/