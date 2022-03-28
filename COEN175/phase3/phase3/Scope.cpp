/*	Stephen Tambussi - 2/6/22
	COEN175 - Phase 3: Symbol Table Construction
*/

# include "Scope.h"
# include <iostream>
# include <algorithm>
using namespace std;


//Constructor Definition
Scope::Scope(Scope *enclosing)
	: _enclosing(enclosing)
{}

void Scope::insert(Symbol *symbol)
{
	_symbols.push_back(symbol);
}

void Scope::remove(const string &name)
{
	Symbol *remove_symbol = lookup(name); //finds nearest symbol with the name
	if(remove_symbol == nullptr) return; //making sure the value exists

	vector<Symbol *>::iterator position = std::find(_symbols.begin(), _symbols.end(), remove_symbol); //get pos of symbol to remove
	if(position != _symbols.end()) //element was found in vector
		_symbols.erase(position); //finally, erase that symbol
}

Symbol * Scope::find(const string &name) const
{
	for(unsigned i = 0; i < _symbols.size(); i++)
	{
		if(_symbols[i]->name() == name) return _symbols[i];
	}
	return nullptr;
}

Symbol * Scope::lookup(const string &name) const
{
	Symbol *symbol = find(name);
	if(symbol != nullptr) return symbol;

	if(_enclosing != nullptr) return _enclosing->lookup(name);
	else
		return nullptr;
}


