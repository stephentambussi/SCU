/*
 *   Stephen Tambussi
 *   COEN225
 *   HW3: problem 2.4
 *   11/1/22
 */
#include <iostream>
#include <ctime>
using namespace std;

void foo(int x)
{
    if (x < 10)
        cout << "x is less than 10\n";
}

int main()
{
    int y = 0;
    const auto now = time(nullptr); // How many seconds since 1970 started?
    if (now == 0)                   // False, unless you have a TARDIS.
        y = 99;
    foo(y);
    return 0;
}
/*
 *   Error:
 *   Valgrind reports 1 error. Similar to the last program, the conditional statement in
 *   the function foo(), relys on variable y that is never initialized. This is because the 
 *   return value of time() will never be 0.
 * 
 *   Fix:
 *   The fix is straightforward. Simply initialize y to 0.
 */