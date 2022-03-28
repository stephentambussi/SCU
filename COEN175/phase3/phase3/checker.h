# ifndef CHECKER_H
# define CHECKER_H

# include <string>
# include <set>
# include <cstdlib>
# include <iostream>

typedef std::string string;

//Function declarations
void openScope();
void closeScope();
void openStruct(const string &name);
void closeStruct(const string &name);
void declareFunction(const string &name, const Type &type);
void defineFunction(const string &name, const Type &type);
void declareVariable(const string &name, const Type &type);
void checkIfStruct(const string &name, const Type &type);
void checkID(const string &name);
# endif /* CHECKER_H */