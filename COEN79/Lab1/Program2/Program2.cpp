//Stephen Tambussi
#include <iostream>
#include <string>
using std::string;//standard namespaces
using std::cout;
using std::cin;
int main()
{
    string input;
    string reverse;//holds reversed string
    string space = " ";//used to incrementally add spaces
    cout << "Enter a string of 10 numbers w/o spaces: \n";
    getline(cin, input);
    for (int i = input.length() - 1; i >= 0; i--)
    {
        reverse.append(1, input[i]);//takes chars of input and adds them to reverse backwards
    }
    for (int i = 0; i < 5; i++)
    {
        cout << input << "      " << reverse << "\n";
        input.insert(0, space);//incrementally adds spaces 
        reverse.insert(0, space);
    }
}
