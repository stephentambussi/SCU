/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 2.1
*   11/1/22
*/
int main() {
    [[maybe_unused]] char *x = new char[100];
    delete [] x; //This is the fix
    return 0;
}
/*
*   Error:
*   Valgrind reports that 100 bytes are lost as they are allocated with the new keyword,
*   but the program exits before they are freed. They are never deleted.
*
*   Fix:
*   Free the memory before the program returns. See above code
*/