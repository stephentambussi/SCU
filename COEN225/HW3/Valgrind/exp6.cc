/*
*   Stephen Tambussi
*   COEN225
*   HW3: problem 2.6
*   11/1/22
*/
#include <iostream>
#include <cstring>		// C-strings: for strcpy()
using namespace std;

int main() {
    char *greeting = new char[1024];
    strcpy(greeting, "Dear");
    //delete [] greeting;
    //Fix - These two lines were swapped.
    cout << greeting << " Sir/Madam\n";
    delete [] greeting;
    return 0;
}
/*
*   Error:
*   Valgrind reports multiple errors. However, they all stem from the same issue. 
*   The program is attempting to read from the greeting char array after it has
*   already been deleted.    
*
*   Fix:
*   The fix is straightforward. Simply, put the cout line before the delete line as
*   seen above.
*/