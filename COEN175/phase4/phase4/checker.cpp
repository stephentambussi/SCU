/*	Stephen Tambussi - 2/20/22
	COEN175 - Phase 4: Type Checking
*/
/*
 * File:	checker.cpp
 *
 * Description:	This file contains the public and private function and
 *		variable definitions for the semantic checker for Simple C.
 *
 *		Extra functionality:
 *		- inserting an undeclared symbol with the error type
 */

#include <map>
#include <set>
#include <iostream>
#include "lexer.h"
#include "checker.h"
#include "Symbol.h"
#include "Scope.h"
#include "Type.h"

using namespace std;

static set<string> functions;
static map<string, Scope *> fields;
static Scope *outermost, *toplevel;
static const Type error;
static Scalar integer("int");

static string undeclared = "'%s' undeclared";
static string redefined = "redefinition of '%s'";
static string redeclared = "redeclaration of '%s'";
static string conflicting = "conflicting types for '%s'";
static string incomplete = "'%s' has incomplete type";
static string nonpointer = "pointer type required for '%s'";

static string e1 = "invalid return type";
static string e2 = "invalid type for test expression";
static string e3 = "lvalue required in expression";
static string e4 = "invalid operands to binary %s";
static string e5 = "invalid operand to unary %s";
static string e6 = "invalid operand in cast expression";
static string e7 = "called object is not a function";
static string e8 = "invalid arguments to called function";
static string e9 = "using pointer to incomplete type";

#define isStructure(t) (t.isStruct() && t.indirection() == 0)

/*
 * Function:	openScope
 *
 * Description:	Create a scope and make it the new top-level scope.
 */

Scope *openScope()
{
    toplevel = new Scope(toplevel);

    if (outermost == nullptr)
        outermost = toplevel;

    return toplevel;
}

/*
 * Function:	closeScope
 *
 * Description:	Remove the top-level scope, and make its enclosing scope
 *		the new top-level scope.
 */

Scope *closeScope()
{
    Scope *old = toplevel;

    toplevel = toplevel->enclosing();
    return old;
}

/*
 * Function:	openStruct
 *
 * Description:	Open a scope for a structure with the specified name.  If a
 *		structure with the same name is already defined, delete it.
 */

void openStruct(const string &name)
{
    if (fields.count(name) > 0)
    {
        delete fields[name];
        fields.erase(name);
        report(redefined, name);
    }

    openScope();
}

/*
 * Function:	closeStruct
 *
 * Description:	Close the scope for the structure with the specified name.
 */

void closeStruct(const string &name)
{
    fields[name] = closeScope();
}

/*
 * Function:	declareSymbol
 *
 * Description:	Declare a symbol with the specified NAME and TYPE.  Any
 *		erroneous redeclaration is discarded.  If a declaration has
 *		multiple errors, only the first error is reported.  To
 *		report multiple errors, remove the "return" statements and,
 *		if desired, the final "else".
 */

void declareSymbol(const string &name, const Type &type, bool isParameter)
{
    Symbol *symbol = toplevel->find(name);

    if (symbol == nullptr)
        toplevel->insert(new Symbol(name, type));
    else if (toplevel != outermost)
    {
        report(redeclared, name);
        return;
    }
    else if (type != symbol->type())
    {
        report(conflicting, name);
        return;
    }

    if (isStructure(type))
    {
        if (isParameter || type.isCallback() || type.isFunction())
            report(nonpointer, name);
        else if (fields.count(type.specifier()) == 0)
            report(incomplete, name);
    }
}

/*
 * Function:	defineFunction
 *
 * Description:	Define a function with the specified NAME and TYPE.  A
 *		function is always defined in the outermost scope.  This
 *		definition always replaces any previous definition or
 *		declaration.  In the case of multiple errors, only the
 *		first error is reported.  To report multiple errors, remove
 *		the "else"s.
 */

Symbol *defineFunction(const string &name, const Type &type)
{
    Symbol *symbol = outermost->find(name);

    if (functions.count(name) > 0)
        report(redefined, name);
    else if (symbol != nullptr && type != symbol->type())
        report(conflicting, name);
    else if (isStructure(type))
        report(nonpointer, name);

    outermost->remove(name);
    delete symbol;

    symbol = new Symbol(name, type);
    outermost->insert(symbol);

    functions.insert(name);
    return symbol;
}

/*
 * Function:	checkIdentifier
 *
 * Description:	Check if NAME is declared.  If it is undeclared, then
 *		declare it as having the error type in order to eliminate
 *		future error messages.
 */

Symbol *checkIdentifier(const string &name)
{
    Symbol *symbol = toplevel->lookup(name);

    if (symbol == nullptr)
    {
        report(undeclared, name);
        symbol = new Symbol(name, error);
        toplevel->insert(symbol);
    }

    return symbol;
}


/* Checker functions below */
Type checkArrayIndex(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    Type t1 = left.promote();
    Type t2 = right.promote();

    if(t1.isPointer() && t2.isInteger())
    {
        if(t1.isStruct())
        {
            if(t1.indirection() < 2 && fields.count(t1.specifier()) == 0) //error - incomplete type
            {
                report(e9);
                return error;
            }
        }
        return Scalar(left.specifier(), t1.indirection() - 1);
    }

    report(e4, "[]");
    return error;
}

Type checkCall(const Type &left, const Parameters &args)
{
    if(left.isError()) return error;

    if(!left.isFunction() && !left.isCallback())
    {
        report(e7);
        return error;
    }

    for(std::vector<Type>::size_type i = 0; i < args.size(); i++)
    {
        if(!args[i].isValue())
        {
            report(e8);
            return error;
        }
    }

    Parameters *declaredArgs = left.parameters();
    if(declaredArgs == nullptr)
        return Scalar(left.specifier(), left.indirection());

    if(declaredArgs->size() != args.size())
    {
        report(e8);
        return error;
    }

    for(std::vector<Type>::size_type i = 0; i < args.size(); i++)
    {
        if(!args[i].isCompatibleWith((*declaredArgs)[i]))
        {
            report(e8);
            return error;
        }
    }
    return Scalar(left.specifier(), left.indirection());
}

Type checkDirectRef(const Type &left, const string &id)
{
    if(left.isError()) return error;
    
    if(!left.isPointer() && left.isStruct() && fields.count(left.specifier()) > 0) //can't be pointer
    {
        Symbol *symbol = fields[left.specifier()]->find(id);
        if(symbol == nullptr)
        {
            report(e4, ".");
            return error;
        }

        return symbol->type();
    }
    
    report(e4, ".");
    return error;
}

Type checkIndirectRef(const Type &left, const string &id)
{
    if(left.isError()) return error;
    
    Type t = left.promote();

    if(t.isPointer() && t.isStruct() && t.indirection() == 1) //can't be pointer to pointer
    {
        if(fields.count(left.specifier()) == 0) //error - incomplete type
        {
            report(e9);
            return error;
        }

        Symbol *symbol = fields[left.specifier()]->find(id);
        if(symbol == nullptr)
        {
            report(e4, "->");
            return error;
        }

        return symbol->type();
    }

    report(e4, "->");
    return error;
}

Type checkNot(const Type &left)
{   
    if(left.isError()) return error;

    if(left.isValue())
        return integer;

    report(e5, "!");
    return error;
}

Type checkNeg(const Type &left)
{
    if(left.isError()) return error;

    Type t = left.promote(); //redundant - keep anyway

    if(t.isInteger())
        return integer;
    
    report(e5, "-");
    return error;
}

Type checkDeref(const Type &left)
{
    if(left.isError()) return error;

    Type t = left.promote(); //redundant -- keep anyway

    if(t.isPointer())
    {
        if(t.isStruct() && fields.count(t.specifier()) == 0 && t.indirection() < 2) //error - incomplete type
        {
            report(e9);
            return error;
        }
        return Scalar(left.specifier(), t.indirection() - 1);
    }
    
    report(e5, "*");
    return error;
}

Type checkAddr(const Type &left, const bool &lvalue)
{
    if(left.isError()) return error;
    //no promotion
    if(lvalue && !left.isCallback())
    {
        return Scalar(left.specifier(), left.indirection() + 1);
    }

    else if(!lvalue)
    {
        report(e3);
        return error;
    }

    else //isCallback == true
    {
        report(e5, "&");
        return error;
    }
}

Type checkSizeof(const Type &left, const string &typespec, unsigned int ptrs)
{
    if(left.isError()) return error;

    //no promotion
    if(left.isFunction())
    {
        report(e5, "sizeof");
        return error;
    }
    if(left.isStruct() && fields.count(left.specifier()) == 0 && left.indirection() < 2) //no incomplete type
    {
        report(e9);
        return error;
    }

    return integer;
}

Type checkTypeCast(const Type &left, const string &typespec, unsigned int ptrs)
{
    if(left.isError()) return error;

    Type t = left.promote();
    Scalar result(typespec, ptrs);
    if((t.isInteger() && result.isInteger()) || (t.isPointer() && result.isPointer()))
    {
        return result;
    }

    report(e6);
    return error;
}

Type checkMul(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    Type t1 = left.promote();
    Type t2 = right.promote();

    if(t1 == integer && t2 == integer)
        return integer;
    
    else
    {
        report(e4, "*");
        return error;
    }
}

Type checkDiv(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    Type t1 = left.promote();
    Type t2 = right.promote();

    if(t1 == integer && t2 == integer)
        return integer;
    
    else
    {
        report(e4, "/");
        return error;
    }
}

Type checkMod(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    Type t1 = left.promote();
    Type t2 = right.promote();

    if(t1 == integer && t2 == integer)
        return integer;
    
    else
    {
        report(e4, "%");
        return error;
    }
}

Type checkAdd(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    Type t1 = left.promote(); //redundant
    Type t2 = right.promote();

    if(t1.isInteger() && t2.isInteger()) return integer;

    else if(t1.isPointer() && t2.isInteger())
    {
        if(t1.isStruct() && fields.count(t1.specifier()) == 0 && t1.indirection() < 2) //error - incomplete type
        {
            report(e9);
            return error;
        }
        return Scalar(t1.specifier(), t1.indirection());
    }

    else if(t1.isInteger() && t2.isPointer()) //addition only
    {
        if(t2.isStruct() && fields.count(t2.specifier()) == 0 && t2.indirection() < 2) //error - incomplete type
        {
            report(e9);
            return error;
        }
        return Scalar(t2.specifier(), t2.indirection());
    }

    report(e4, "+");
    return error;
}

Type checkSub(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    Type t1 = left.promote(); //redundant
    Type t2 = right.promote();

    if(t1.isInteger() && t2.isInteger()) return integer;

    else if(t1.isPointer() && t2.isInteger())
    {
        if(t1.isStruct() && fields.count(t1.specifier()) == 0 && t1.indirection() < 2) //error - incomplete type
        {
            report(e9);
            return error;
        }
        return Scalar(t1.specifier(), t1.indirection());
    }

    else if((t1.isPointer() && t2.isPointer()) && (t1 == t2)) //subtraction only
    {
        if((t1.isStruct() && fields.count(t1.specifier()) == 0 && t1.indirection() < 2) || (t2.isStruct() && fields.count(t2.specifier()) == 0 && t2.indirection() < 2)) //error - incomplete type
        {
            report(e9);
            return error;
        }
        return integer;
    }
    
    report(e4, "-");
    return error;
}

Type checkLT(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    if(left.isCompatibleWith(right))
        return integer;
    
    report(e4, "<");
    return error;
}

Type checkGT(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    if(left.isCompatibleWith(right))
        return integer;
    
    report(e4, ">");
    return error;
}

Type checkLEQ(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    if(left.isCompatibleWith(right))
        return integer;
    
    report(e4, "<=");
    return error;
}

Type checkGEQ(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    if(left.isCompatibleWith(right))
        return integer;
    
    report(e4, ">=");
    return error;
}

Type checkEqual(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    if(left.isCompatibleWith(right))
        return integer;
    
    report(e4, "==");
    return error;
}

Type checkNotEqual(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    if(left.isCompatibleWith(right))
        return integer;
    
    report(e4, "!=");
    return error;
}

Type checkLogicalAnd(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    if(left.isValue() && right.isValue())
        return integer;

    report(e4, "&&");
    return error;
}

Type checkLogicalOr(const Type &left, const Type &right)
{
    if(left.isError() || right.isError()) return error;

    if(left.isValue() && right.isValue())
        return integer;

    report(e4, "||");
    return error;
}

void checkAssignment(const Type &left, const Type &right, const bool &leftVal)
{
    if(left.isError() || right.isError()) return;

    if(!leftVal)
    {
        report(e3);
        return;
    }
    if(!left.isCompatibleWith(right))
    {
        report(e4, "=");
        return;
    }
    return;
}

void checkReturn(const Type &t, const Type &return_type)
{
    if(!t.isCompatibleWith(return_type))
    {
        report(e1);
        return;
    }
    return;
}

void checkWhile(const Type &t)
{
    if(!t.isValue())
    {
        report(e2);
    }
}

void checkFor(const Type &t)
{
    if(!t.isValue())
    {
        report(e2);
    }
}

void checkIf(const Type &t)
{
    if(!t.isValue())
    {
        report(e2);
    }
}