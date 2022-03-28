/*	Stephen Tambussi - 2/6/22
	COEN175 - Phase 3: Symbol Table Construction
*/
# include "Scope.h"
# include "lexer.h"
# include "checker.h"

using namespace std;

static set<string> structures;

static Scope *current = nullptr;
static string e1 = "redefinition of '%s'";
static string e2 = "conflicting types for '%s'";
static string e3 = "redeclaration of '%s'";
static string e4 = "'%s' undeclared";
static string e5 = "pointer type required for '%s'";
static string e6 = "'%s' has incomplete type";

void openScope()
{
    cout << "Open Scope" << endl;
    if(current == nullptr) //file/global scope
        current = new Scope();
    
    else //function/block scope
    {
        Scope *new_scope = new Scope(current);
        current = new_scope;
    }
}

void closeScope()
{
    cout << "Close Scope" << endl;
    current = current->enclosing();
}

void openStruct(const string &name)
{
    if(structures.count(name) > 0)
        report(e1, name);
    
    openScope();
}

void closeStruct(const string &name)
{
    closeScope();
    structures.insert(name);
}

void declareFunction(const string &name, const Type &type)
{
    Symbol *symbol = current->find(name);

    if(symbol == nullptr)
    {
        symbol = new Symbol(name, type);
        current->insert(symbol);
        cout << "declare " << name << " as " << type << endl;
    }
    else if(symbol->type() != type) //previous fun declaration not identical
    {
        report(e2, name);
    }
    else if(symbol->type().parameters() != nullptr) //function previously defined
    {
        report(e1, name);
    }
}

void defineFunction(const string &name, const Type &type)
{
    Symbol *symbol = current->find(name);

    if(symbol == nullptr)
    {
        symbol = new Symbol(name, type);
        current->insert(symbol);
        cout << "define " << name << " as " << type << endl;
    }
    else if(symbol->type().parameters() != nullptr) //function previously defined
    {
        report(e1, name);
    }
    else if(symbol->type() != type) //previous fun declaration not identical
    {
        report(e2, name);
    }
}

void declareVariable(const string &name, const Type &type)
{
    Symbol *symbol = current->find(name);

    if(symbol == nullptr) //add symbol
    {
        //check if type is a struct type, defined or indirection > 0
        if(type.isStruct() && type.indirection() == 0 && structures.count(type.specifier()) == 0) 
            report(e6, name);
        else
        {
            symbol = new Symbol(name, type);
            current->insert(symbol);
            cout << "declare " << name << " as " << type << endl;
        }
    }
    else if(current->enclosing() != nullptr) //if symbol found and already declared
    {
        report(e3, name);
    }
    else if(symbol->type() != type) //if symbol found, but has two types
    {
        report(e2, name);
    }
}

void checkIfStruct(const string &name, const Type &type) //for function, parameters, and callbacks
{
    if(type.isStruct() && type.indirection() == 0)
    {
        report(e5, name);
    } 
}

void checkID(const string &name)
{
    Symbol *s = current->lookup(name);
    if(s == nullptr)
        report(e4, name);
}