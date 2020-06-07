//Stephen Tambussi
#include <iostream>
#include <string>
using std::string;//standard namespace
using std::cout;
using std::cin;
int main()
{
    string input;
    int alnum = 0;//variable to count alphanumeric characters
    int other = 0;//counts everything else
    cout << "Enter some text and this program will count the characters:\n";
    getline(cin, input);//gets users input
    for (int i = 0; i < input.length(); i++)//iterates through user entered text
    {
        if (isalnum(input[i]))
            alnum++;
        else if (isalnum(input[i]) == 0 && input[i] != ' ')//if not alphanumeric and not a space(so not to count spaces)
            other++;
    }
    cout << "Input has " << alnum << " alphanumerical characters and " << other << " non-alphanumerical characters.";
    //prints out
}