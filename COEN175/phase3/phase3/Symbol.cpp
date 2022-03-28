/*	Stephen Tambussi - 2/6/22
	COEN175 - Phase 3: Symbol Table Construction
*/

# include "Symbol.h"

//Constructor definition of symbol class
Symbol::Symbol(const string &name, const Type &type)
    : _name(name), _type(type)
{}