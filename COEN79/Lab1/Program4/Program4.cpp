//Stephen Tambussi
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
int main()
{
    string input;
    cout << "Think of a number between 1 and 20. Press Enter when you are ready.";
    if (cin.get() == '\n')//simple way of registering 'enter' keypress
    {
        for (int i = 0; i < 20; i++)//iterates 20 times
        {
            cout << "Is the number " << i+1 << ", Yes(Y) or No(N)?\n";//asks question for each number
            cin >> input;//takes user input and stores in string 
            if (input == "Y" || input == "y" || input == "Yes" || input == "yes")//every possible yes 
            {
                cout << "I found the number in " << i+1 << " steps";//states # of steps it took
                break;//ends for loop
            }
        }
    }
    else
        cout << "Please restart program and press enter";//if user didn't press enter
}

