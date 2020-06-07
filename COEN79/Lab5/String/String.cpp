//Stephen Tambussi
#include "mystring.h"
#include <iostream>
#include <cassert>
#include <string.h>
#include <cctype>  

using namespace std;
namespace coen79_lab5
{
	string::string(const char str[])
	{
		current_length = strlen(str);
		allocated = current_length + 1;
		characters = new char[allocated];
		strncpy(characters, str, allocated);
	}
	string::string(char c)
	{
		current_length = 1;
		allocated = current_length + 1;
		characters = new char[allocated];
		characters[0] = c;
		characters[1] = '\0';
	}
	string::string(const string& source)
	{
		current_length = source.current_length;
		allocated = source.allocated;
		characters = new char[source.current_length];
		strncpy(characters, source.characters, source.current_length);
	}
	string::~string()
	{
		allocated = 0;
		current_length = 0;
		delete[] characters;
	}
	void string::operator +=(const string& addend)
	{
		current_length = current_length + addend.current_length;
		allocated = current_length + 1;
		reserve(allocated);
		strncat(characters, addend.characters, addend.current_length);
	}
	void string::operator +=(const char addend[])
	{
		current_length = current_length + strlen(addend);
		allocated = current_length + 1;
		reserve(allocated);
		strncat(characters, addend, strlen(addend));
	}
	void string::operator +=(char addend)
	{
		current_length = current_length + 1;
		allocated = current_length + 1;
		reserve(allocated);
		characters[current_length] = addend;
	}
	void string::reserve(size_t n)
	{
		char* temp = new char[n];
		if (characters != NULL)
		{
			strncpy(temp, characters, current_length);
			delete[] characters;
		}
		characters = temp;
	}
	string& string::operator=(const string& source)
	{
		this->dlt(0, current_length);
		if (current_length != source.current_length)
		{
			allocated = source.allocated;
			reserve(allocated);
		}
		strncpy(characters, source.characters, source.current_length);
		current_length = source.current_length;
		return *this;
	}
	void string::insert(const string& source, unsigned int position) 
	{
		assert(position <= length());                                      
		size_t total_length = current_length + source.current_length;   
		if (allocated < (total_length)) reserve(total_length);                                      
		for (int i = length(); i > position; i--)                        
			characters[i] = characters[i - 1];
		for (int i = 0; i < source.length(); i++)                        
			characters[position + i] = source.characters[i];           
		current_length = total_length;                                  
	}
	void string::dlt(unsigned int position, unsigned int num) 
	{
		assert((position + num) <= length());                         
		for (int i = position; i < length(); i++)                        
			characters[i] = characters[i + num];                          
		current_length = current_length - num;                           
	}
	void string::replace(char c, unsigned int position) 
	{
		assert(position < length());                                    
		characters[position] = c;                                       
	}
	void string::replace(const string& source, unsigned int position) 
	{
		assert((position + source.length()) <= length());            
		int i, j;
		for (i = position, j = 0; i < (position + source.length()); i++) 
			characters[i] = source[j++];                                
	}
	char string::operator[](size_t position) const 
	{
		assert(position < length());                                    
		return characters[position];                                    
	}
	int string::search(char c) const 
	{
		for (int i = 0; i < length(); i++) {                             
			if (characters[i] == c)                                     
				return i;                                               
		}
		return -1;                                                      
	}
	int string::search(const string& substring) const 
	{
		char* temp = strstr(characters, substring.characters);          
		if (temp != NULL)                                            
			return temp[0] - characters[0];                             
		return -1;                                                      
	}
	unsigned int string::count(char c) const 
	{
		unsigned int count = 0;
		for (int i = 0; i < length(); i++) {                             
			if (characters[i] == c)                                      
				count++;                                              
		}
		return count;
	}
	string operator+(const string& s1, const string& s2) 
	{
		string temp;                                                    
		temp.reserve(s1.length() + s2.length() + 1);                        
		temp += s1;                                                     
		temp += s2;                                                     
		return temp;                                                    
	}
	string operator+(const string& s1, const char addend[]) 
	{
		string temp;                                                    
		temp.reserve(s1.length() + strlen(addend) + 1);                     
		temp += s1;                                                     
		temp += addend;                                                 
		return temp;                                                    
	}
	std::istream& operator >> (std::istream& ins, string& target) 
	{
		char* buf = new char[100];                                   
		while (ins && isspace(ins.peek()))                               
			ins.ignore();                                               
		ins >> buf;                                                  
		target = string(buf);                                        
		return ins;                                                     
	}
	std::ostream& operator <<(std::ostream& outs, const string& source) 
	{
		outs << source.characters;                                      
		return outs;                                                    
	}
	bool operator ==(const string& s1, const string& s2)                // Checks if the two strings are the same
	{
		return (strcmp(s1.characters, s2.characters) == 0);
	}

	bool operator !=(const string& s1, const string& s2)                
	{
		return (strcmp(s1.characters, s2.characters) != 0);
	}
	bool operator > (const string& s1, const string& s2)                
	{
		return (strcmp(s1.characters, s2.characters) > 0);
	}
	bool operator < (const string& s1, const string& s2)                
	{
		return (strcmp(s1.characters, s2.characters) < 0);
	}
	bool operator >=(const string& s1, const string& s2)                
	{
		return ((s1 > s2) || (s1 == s2));
	}                      
	bool operator <=(const string& s1, const string& s2)                
	{
		return ((s1 < s2) || (s1 == s2));
	}
}
