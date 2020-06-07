//Stephen Tambussi
#include <iostream>
#include <string>
#include <fstream>//file i/o header
using std::string;
using std::cout;
using std::cin;
using std::ifstream;//for reading file
int main() {
    string line;
    string big;
    ifstream myfile("input.txt");//specifies file name
    if (myfile.is_open())//opens file
    {
        while (getline(myfile, line))//gets text line by line
        {
            if (line.length() > 10)//if line is greater than 10 characters
            {
                for (int i = 0; i < line.length(); i++)
                {
                    if (isalpha(line[i]))
                        big.append(1, toupper(line[i]));//converts to uppercase and appends to string
                }
            }
            cout << big << '\n';
            big = "";//reset string to empty after printing
        }
        myfile.close();//close file
    }
    else cout << "Unable to open file";//if file does not exist or cannot be open
    return 0;
}