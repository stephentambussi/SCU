//Stephen Tambussi - 1/9/22
//COEN175 - Phase 1: Lexical Analysis

#include <iostream>
#include <string>
#include <set>

using namespace std;

string keywords[] = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
                    "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", "return", "short",
                    "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
                    "while"};
std::set<std::string> keyword_set(keywords, keywords+32);

int main()
{
    std::string token;
    int c = cin.get();

    while(!cin.eof()) //While there is still input, execute
    {
        token.clear();

        //Ignore white space
        if (isspace(c))
            c = cin.get();
        
        //Integer
        else if(isdigit(c))
        {
            token += c;
            c = cin.get();
            while(isdigit(c))
            {
                token += c;
                c = cin.get();
            }
            cout << "number:" << token << endl;
            continue; //ignore everything after this and continute next iteration of loop
        }

        //String - no new line or double quote inside string without being preceded by backslash
        else if(c == '\"') //double quote
        {
            token += c;
            c = cin.get();
            int stop_flag = 0;
            while(stop_flag != 1)
            {
                if(c == '\\') //backslash
                {
                    //Add whatever is after the backslash
                    token += c;
                    c = cin.get();
                    token += c;
                    c = cin.get();
                    continue;
                }
                else if(c == '\"')
                    stop_flag = 1;
                else if(c == '\n')
                    cerr << "Illegal newline character" << endl;
                token += c;
                c = cin.get();
            }
            cout << "string:" << token << endl;
            continue;
        }

        //Character - no new line or single quote inside char without being preceded by backslash
        else if(c == '\'') //single quote
        {
            token += c;
            c = cin.get();
            int stop_flag = 0;
            while(stop_flag != 1)
            {
                if(c == '\\') //backslash
                {
                    //Add whatever is after the backslash
                    token += c;
                    c = cin.get();
                    token += c;
                    c = cin.get();
                    continue;
                }
                else if(c == '\'')
                    stop_flag = 1;
                else if(c == '\n')
                    cerr << "Illegal newline character" << endl;
                token += c;
                c = cin.get();
            }
            cout << "character:" << token << endl;
            continue;
        }

        //Identifiers and Keywords
        else if(isalpha(c) || c == '_') //identifiers either start with letter or underscore, keywords contain letters only
        {
            token += c;
            c = cin.get();
            while(isalnum(c) || c == '_') //the rest of the identifier can be letters, underscores, or digits
            {
                token += c;
                c = cin.get();
            }
            if(keyword_set.count(token) > 0) //if keyword found in set
                cout << "keyword:" << token << endl;
            else
                cout << "identifier:" << token << endl;
            continue;
        }

        //Operators and comments
        else
        {
            switch(c)
            {
                case '=': //assignment
                    token += c;
                    c = cin.get();
                    if(c == '=') //equal to
                    {
                        token += c;
                        c = cin.get();
                    }
                    break;
                case '|': //bitwise or
                    token += c;
                    c = cin.get();
                    if(c == '|') //logical or
                    {
                        token += c;
                        c = cin.get();
                    }
                    break;
                case '&': //bitwise and
                    token += c;
                    c = cin.get();
                    if(c == '&') //logical and
                    {
                        token += c;
                        c = cin.get();
                    }
                    break;
                case '!': //logical not
                    token += c;
                    c = cin.get();
                    if(c == '=') //not equals
                    {
                        token += c;
                        c = cin.get();
                    }
                    break;
                case '<': //less than
                    token += c;
                    c = cin.get();
                    if(c == '=') //less than or equal to
                    {
                        token += c;
                        c = cin.get();
                    }
                    break;
                case '>': //greater than
                    token += c;
                    c = cin.get();
                    if(c == '=') //greater than or equal to
                    {
                        token += c;
                        c = cin.get();
                    }
                    break;
                case '+': //addition
                    token += c;
                    c = cin.get();
                    if(c == '+') //increment
                    {
                        token += c;
                        c = cin.get();
                    }
                    break;
                case '-': //subtraction
                    token += c;
                    c = cin.get();
                    if(c == '-') //decrement
                    {
                        token += c;
                        c = cin.get();
                    }
                    else if(c == '>') //arrow 
                    {
                        token += c;
                        c = cin.get();
                    }
                    break;
                case '*': //multiplication
                    token += c;
                    c = cin.get();
                    break;
                case '/': //division or comment
                    token += c;
                    c = cin.get();
                    if(c == '*') //comment case
                    {
                        token.clear();
                        c = cin.get();
			int stop = 0;
                        while(stop != 1)
			{
				if(c == '*' && cin.peek() == '/') //look for end comment symbol
				{
					c = cin.get();
					stop = 1;
				}
				c = cin.get();
			}
                        c = cin.get();
                        continue;
                    }
                    break;
                case '%': //modulus
                    token += c;
                    c = cin.get();
                    break;
                case '.': //period
                    token += c;
                    c = cin.get();
                    break;
                case '(': //left parenthese
                    token += c;
                    c = cin.get();
                    break;
                case ')': //right parenthese
                    token += c;
                    c = cin.get();
                    break;
                case '[': //left bracket
                    token += c;
                    c = cin.get();
                    break;
                case ']': //right bracket
                    token += c;
                    c = cin.get();
                    break;
                case '{': //left brace
                    token += c;
                    c = cin.get();
                    break;
                case '}': //right brace
                    token += c;
                    c = cin.get();
                    break;
                case ';': //terminator
                    token += c;
                    c = cin.get();
                    break;
                case ':': //colon
                    token += c;
                    c = cin.get();
                    break;
                case ',': //comma
                    token += c;
                    c = cin.get();
                    break;
                default:
                    c = cin.get();
            }
            cout << "operator:" << token << endl;
        }
    }
    return 0;
}
