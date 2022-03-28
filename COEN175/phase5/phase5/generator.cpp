/*	Stephen Tambussi - 2/27/22
	COEN175 - Phase 5: Storage Allocation
*/
# include "Tree.h"
# include "generator.h"
# include "Type.h"
# include <iostream>

using namespace std;
static ostream &operator<<(ostream &ostr, Expression *expr);

void generateGlobals(Scope *global)
{
    for (auto symbol : global->symbols())
    {
        if (!symbol->type().isFunction())
            cout << "\t.comm\t" << symbol->name() << ", " << symbol->type().size() << endl;
    }
}

static ostream &operator<<(ostream &ostr, Expression *expr)
{
    expr->operand(ostr);
    return ostr;
}

void Number::operand(ostream &ostr) const
{
    ostr << "$" << _value;
}

void Identifier::operand(ostream &ostr) const
{
    if(_symbol->_offset == 0)
        ostr << _symbol->name();
    else
        ostr << _symbol->_offset << "(%ebp)";
}

void Procedure::generate() //function definitions
{
    cout << ".globl\t" << _id->name() << endl;
    cout << _id->name() << ":" << endl;
    //Prologue
    cout << "\tpushl\t%ebp" << endl;
    cout << "\tmovl\t%esp, %ebp" << endl;

    //Parameters then declarations
    Parameters *params = _id->type().parameters();
    Symbols decls = _body->declarations()->symbols();

    //Parameter offsets
    int size = 0;
    int offset = 8; //first parameter is 8 bytes up
    for (size_t i = 0; i < params->size(); i++)
    {
        size = params->at(i).size();
        decls.at(i)->_offset = offset;
        cerr << decls.at(i)->name() << ": +" << offset << endl;
        offset += (size % 4 == 0) ?  size : size + (size % 4);
    }

    //Declaration offsets
    offset = 0;
    for (size_t i = params->size(); i < decls.size(); i++)
    {
        offset -= decls.at(i)->type().size();
        decls.at(i)->_offset = offset;
        cerr << decls.at(i)->name() << ": " << offset << endl;
    }
    
    //End of Prologue
    cout << "\tsubl \t$" << offset * -1 << ", %esp" << endl;

    _body->generate();

    //Epilogue
    cout << "\tmovl\t%ebp, %esp" << endl;
    cout << "\tpopl\t%ebp" << endl;
    cout << "\tret" << endl;
}

void Simple::generate()
{
    _expr->generate();
}

void Block::generate()
{
    for(auto stmt : _stmts)
        stmt->generate();
}

void Assignment::generate()
{
    cout << "\tmovl\t" << _right << ", " << _left << endl;
}

void Call::generate()
{
    int stack_space = 0;

    //Push args - last arg pushed first
    for (int i = _args.size() - 1; i >= 0; i--)
    {
        Expression *arg = _args.at(i);
        cout << "\tpushl\t" << arg << endl;
        stack_space += arg->type().size();

    }
    // Call function
    cout << "\tcall\t" << _expr << endl;

    // Reclaim stack space
    cout << "\taddl\t$" << stack_space << ", %esp" << endl;
}