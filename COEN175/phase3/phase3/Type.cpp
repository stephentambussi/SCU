/*	Stephen Tambussi - 2/6/22
	COEN175 - Phase 3: Symbol Table Construction
*/

# include "Type.h"
# include "tokens.h"

//Constructor definition of type class
Type::Type(int kind, const string &specifier, unsigned indirection)
{
    _kind = kind;
    _specifier = specifier;
    _indirection = indirection;

    _length = 0;
    _parameters = nullptr;
}

//Default constructor definition of type class
Type::Type()
    : _kind(ERROR), _specifier("error"), _indirection(0)
{
    _length = 0;
    _parameters = nullptr;
}

/* Scratch work for function and callback equivalence check for below function
 * int f();         params: nullptr
 * int f(void) {}   params: []
 * int f(int x) {}  params: [int]
*/
bool Type::operator ==(const Type &rhs) const
{
    if(_kind != rhs._kind) return false;

    if(_kind == ERROR) return true;

    if(_specifier != rhs._specifier) return false;

    if(_indirection != rhs._indirection) return false;

    if(_kind == SCALAR) return true;

    if(_kind == ARRAY)
        return _length == rhs._length; //checks if array lengths are the same
    
    if(!_parameters || !rhs._parameters) //if parameters have not been specified yet
        return true;
    
    return *_parameters == *rhs._parameters; //checks if values of parameter lists are the same using overloaded == operator (recursive)
}

bool Type::operator !=(const Type &rhs) const
{
    return !operator==(rhs);
}

bool Type::isStruct() const
{
    return _kind != ERROR && _specifier != "int" && _specifier != "char";
}

std::ostream &operator <<(std::ostream &os, const Type &type) 
{
    std::string kind;
    if(type.isArray()) kind = "ARRAY";
    else if(type.isCallback()) kind = "CALLBACK";
    else if(type.isError()) kind = "ERROR";
    else if(type.isFunction()) kind = "FUNCTION";
    else 
    {
        assert(type.isScalar());
        kind = "SCALAR";
    }
    os << "(" << type.specifier() << ", " << type.indirection() << ", " << kind << ")";
    return os;
}
