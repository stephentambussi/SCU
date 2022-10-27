/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 2.10
*   11/1/22
*/
#include <iostream>
using namespace std;

int main()
{
    unsigned int a = 30, b = 20;
    signed int diff = b - a; //This is the fix
    cout << "diff is " << diff << endl;
    return 0;
}
/*
*   Error:
*   Valgrind reports no errors in this program. However, there is still an error present. The error is an integer
*   underflow. Since the program is performing 20 - 30, the user would expect the resulting value
*   to be -10. But, since a and b are unsigned ints, their minimum possible value is 0 (they can't be negative).
*   As a result, the value wraps around and the program outputs 4,294,967,286, 10 less than the maximum value 
*   for unsigned ints (4,294,967,295). Valgrind does not report this an error because it focuses on memory related
*   errors while this error is integer underflow.
*
*   Fix:
*   To fix the integer underflow issue, simply change the type of the diff variable to signed int.
*/