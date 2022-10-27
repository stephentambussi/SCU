/*
 *   Stephen Tambussi
 *   COEN225
 *   HW3: problem 2.3
 *   11/1/22
 */
#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    int x = 0; // this is the fix

    if (time(nullptr) == 42) // no time machine available
        x = 42;              // so this will not happen

    if (x == 0)
        cout << "x is zero\n";
    else
        cout << "x is non-zero\n";

    return 0;
}
/*
 *   Error:
 *   Valgrind reports 1 error. The conditional statements rely on the variable x which
 *   is never initialized. It is never initialized because, as the code comments hint at,
 *   the return value of time() will never be 42. The time() function returns the number of 
 *   seconds that have passed since the start of 1970.
 *
 *   Fix:
 *   The fix is straightforward. Simply initialize x to 0.
 */