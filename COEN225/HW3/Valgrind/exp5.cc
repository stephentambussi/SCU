/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 2.5
*   11/1/22
*/
int main() {
    char x[10] = {00,11,22,33,44,55,66,77,88,99}; //This line is okay since characters can be represented by their ASCII decimal values
    x[9] = 'a'; //This is the fix --> write inside array bounds
    return x[0];
}
/*
*   Error:
*   Valgrind reports 1 error, an invalid write. The array of chars x is indexed from 0-9 as it has 10 elements.
*   The line immediately after x's initialization is attempting to write outside the array bounds for x at
*   index 12345678.
*   
*   Fix:
*   The fix is straightforward. Simply change the index of the error line.
*/