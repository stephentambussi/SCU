/*	Stephen Tambussi - 3/11/22
    COEN175 - Phase 6: Code Generation
*/
/*
 * File:	generator.cpp
 *
 * Description:	This file contains the public and member function
 *		definitions for the code generator for Simple C.
 *
 *		Extra functionality:
 *		- putting all the global declarations at the end
 */

#include <cassert>
#include <iostream>
#include <map>
#include "generator.h"
#include "machine.h"
#include "Label.h"
#include "string.h"
#include "Tree.h"

using namespace std;

static int offset;
static string funcname;
static ostream &operator<<(ostream &ostr, Expression *expr);
void assign(Expression *expr, Register *reg);
void load(Expression *expr, Register *reg);
Register *getreg();

static Register *eax = new Register("%eax", "%al");
static Register *ecx = new Register("%ecx", "%cl");
static Register *edx = new Register("%edx", "%dl");

static vector<Register *> registers = {eax, ecx, edx};

static map<string, Label *> strings;

/*
 * Function:	align (private)
 *
 * Description:	Return the number of bytes necessary to align the given
 *		offset on the stack.
 */

static int align(int offset)
{
    if (offset % STACK_ALIGNMENT == 0)
        return 0;

    return STACK_ALIGNMENT - (abs(offset) % STACK_ALIGNMENT);
}

/*
 * Function:	operator << (private)
 *
 * Description:	Convenience function for writing the operand of an
 *		expression using the output stream operator.
 */

static ostream &operator<<(ostream &ostr, Expression *expr)
{
    if (expr->_register != nullptr)
        return ostr << expr->_register;

    expr->operand(ostr);
    return ostr;
}

/*
 * Function:	Expression::operand
 *
 * Description:	Write an expression as an operand to the specified stream.
 */

void Expression::operand(ostream &ostr) const
{
    assert(_offset != 0);
    ostr << _offset << "(%ebp)";
}

/*
 * Function:	Identifier::operand
 *
 * Description:	Write an identifier as an operand to the specified stream.
 */

void Identifier::operand(ostream &ostr) const
{
    if (_symbol->_offset == 0)
        ostr << global_prefix << _symbol->name();
    else
        ostr << _symbol->_offset << "(%ebp)";
}

/*
 * Function:	Number::operand
 *
 * Description:	Write a number as an operand to the specified stream.
 */

void Number::operand(ostream &ostr) const
{
    ostr << "$" << _value;
}

/*
 * Function:	Call::generate
 *
 * Description:	Generate code for a function call expression.
 *
 * 		On a 32-bit Linux platform, the stack needs to be aligned
 * 		on a 4-byte boundary.  (Online documentation seems to
 * 		suggest that 16 bytes are required, but 4 bytes seems to
 * 		work and is much easier.)  Since all arguments are 4-bytes
 *		wide, the stack will always be aligned.
 *
 *		On a 32-bit OS X platform, the stack needs to aligned on a
 *		16-byte boundary.  So, if the stack will not be aligned
 *		after pushing the arguments, we first adjust the stack
 *		pointer.  However, this trick only works if none of the
 *		arguments are themselves function calls.
 *
 *		To handle nested function calls, we need to generate code
 *		for the nested calls first, which requires us to save their
 *		results and then push them on the stack later.  For
 *		efficiency, we only first generate code for the nested
 *		calls, but generate code for ordinary arguments in place.
 */

void Call::generate()
{
    unsigned numBytes;

    /* Generate code for any nested function calls first. */

    numBytes = 0;

    for (int i = _args.size() - 1; i >= 0; i--)
    {
        numBytes += _args[i]->type().size();

        if (STACK_ALIGNMENT != SIZEOF_REG && _args[i]->_hasCall)
            _args[i]->generate();
    }

    /* Align the stack if necessary. */

    if (align(numBytes) != 0)
    {
        cout << "\tsubl\t$" << align(numBytes) << ", %esp" << endl;
        numBytes += align(numBytes);
    }

    /* Generate code for any remaining arguments and push them on the stack. */

    for (int i = _args.size() - 1; i >= 0; i--)
    {
        if (STACK_ALIGNMENT == SIZEOF_REG || !_args[i]->_hasCall)
            _args[i]->generate();

        cout << "\tpushl\t" << _args[i] << endl;
        assign(_args[i], nullptr);
    }

    /* Call the function and then reclaim the stack space. */

    load(nullptr, eax);
    load(nullptr, ecx);
    load(nullptr, edx);

    if (_expr->type().isCallback())
    {
        _expr->generate();

        if (_expr->_register == nullptr)
            load(_expr, getreg());

        cout << "\tcall\t*" << _expr << endl;
        assign(_expr, nullptr);
    }
    else
        cout << "\tcall\t" << _expr << endl;

    if (numBytes > 0)
    {
        cout << "\taddl\t$" << numBytes << ", %esp" << endl;
    }

    assign(this, eax);
}

/*
 * Function:	Block::generate
 *
 * Description:	Generate code for this block, which simply means we
 *		generate code for each statement within the block.
 */

void Block::generate()
{
    for (auto stmt : _stmts)
    {
        stmt->generate();

        for (auto reg : registers)
            assert(reg->_node == nullptr);
    }
}

/*
 * Function:	Simple::generate
 *
 * Description:	Generate code for a simple (expression) statement, which
 *		means simply generating code for the expression.
 */

void Simple::generate()
{
    _expr->generate();
    assign(_expr, nullptr);
}

/*
 * Function:	Procedure::generate
 *
 * Description:	Generate code for this function, which entails allocating
 *		space for local variables, then emitting our prologue, the
 *		body of the function, and the epilogue.
 */

void Procedure::generate()
{
    int param_offset;

    /* Assign offsets to the parameters and local variables. */

    param_offset = 2 * SIZEOF_REG;
    offset = param_offset;
    allocate(offset);

    /* Generate our prologue. */

    funcname = _id->name();
    cout << global_prefix << funcname << ":" << endl;
    cout << "\tpushl\t%ebp" << endl;
    cout << "\tmovl\t%esp, %ebp" << endl;
    cout << "\tsubl\t$" << funcname << ".size, %esp" << endl;

    /* Generate the body of this function. */

    _body->generate();

    /* Generate our epilogue. */

    cout << endl
         << global_prefix << funcname << ".exit:" << endl;
    cout << "\tmovl\t%ebp, %esp" << endl;
    cout << "\tpopl\t%ebp" << endl;
    cout << "\tret" << endl
         << endl;

    offset -= align(offset - param_offset);
    cout << "\t.set\t" << funcname << ".size, " << -offset << endl;
    cout << "\t.globl\t" << global_prefix << funcname << endl
         << endl;
}

/*
 * Function:	generateGlobals
 *
 * Description:	Generate code for any global variable declarations.
 */

void generateGlobals(Scope *scope)
{
    const Symbols &symbols = scope->symbols();

    for (auto symbol : symbols)
        if (!symbol->type().isFunction())
        {
            cout << "\t.comm\t" << global_prefix << symbol->name() << ", ";
            cout << symbol->type().size() << endl;
        }
    if(!strings.empty())
    {
        cout << "\t.data" << endl;
        for(auto i = strings.begin(); i != strings.end(); i++)
            cout << *(i->second) << ":" << "\t.asciz\t" << "\"" << escapeString(i->first) << "\"" << endl;
    }
}

static void findBaseAndOffset(Expression *expr, Expression *&base, int &offset)
{
    int field;

    base = expr;
    offset = 0;

    while(base->isField(base, field))
        offset += field;
}

/*
 * Function:	Assignment::generate
 *
 * Description:	Generate code for an assignment statement.
 */
void Assignment::generate()
{
    int offset;
    Expression *base;
    Expression *ptr;

    findBaseAndOffset(_left, base, offset);

    _right->generate();

    if (base->isDereference(ptr))
    {
        ptr->generate();

        if (ptr->_register == nullptr)
            load(ptr, getreg());

        if (_right->_register == nullptr)
            load(_right, getreg());

        if (_left->type().size() == 4)
            cout << "\tmovl\t" << _right << ", " << offset << "(" << ptr << ")" << endl;
        else if (_left->type().size() == 1)
            cout << "\tmovb\t" << _right->_register->byte() << ", " << offset << "(" << ptr << ")" << endl;

        assign(ptr, nullptr);
    }
    else
    {
        if (_right->_register == nullptr)
            load(_right, getreg());

        if (_left->type().size() == 4)
            cout << "\tmovl\t" << _right << ", " << offset << "+" << base << endl;
        else if (_left->type().size() == 1)
            cout << "\tmovb\t" << _right->_register->byte() << ", " << offset << "+" << base << endl;
    }

    assign(_right, nullptr);
}

void assign(Expression *expr, Register *reg)
{ // Maintain proper mappings between Register and Expression type
    if (expr != nullptr)
    {
        if (expr->_register != nullptr)
            expr->_register->_node = nullptr;

        expr->_register = reg;
    }
    if (reg != nullptr)
    {
        if (reg->_node != nullptr)
            reg->_node->_register = nullptr;

        reg->_node = expr;
    }
}

void load(Expression *expr, Register *reg)
{
    if (reg->_node != expr)
    {
        if (reg->_node != nullptr) // if register is allocated
        {
            unsigned n = reg->_node->type().size();
            offset -= n;
            reg->_node->_offset = offset;
            // Spill register to a temporary on the stack
            cout << (n == 1 ? "\tmovb\t" : "\tmovl\t");
            cout << reg << ", " << offset << "(%ebp)" << endl;
        }

        if (expr != nullptr) // load expression into register
        {
            unsigned n = expr->type().size();
            cout << (n == 1 ? "\tmovb\t" : "\tmovl\t");
            cout << expr << ", " << reg->name(n) << endl;
        }

        assign(expr, reg);
    }
}

Register *getreg()
{
    // find next available (empty) register for allocation
    for (auto reg : registers)
    {
        if (reg->_node == nullptr)
            return reg;
    }
    // if none available, spill the first register to make it available
    load(nullptr, registers[0]);
    return registers[0];
}

static void compute(Expression *result, Expression *left, Expression *right, const string &opcode)
{
    // generate left and right side
    left->generate();
    right->generate();

    if (left->_register == nullptr) // load left if not loaded
        load(left, getreg());

    // Run operation
    cout << "\t" << opcode << "\t" << right << ", " << left << endl;

    // unassign right register
    assign(right, nullptr);

    // Assign left register to result expression
    assign(result, left->_register);
}

void Add::generate()
{
    compute(this, _left, _right, "addl");
}

void Subtract::generate()
{
    compute(this, _left, _right, "subl");
}

void Multiply::generate()
{
    compute(this, _left, _right, "imull");
}

static void divide(Expression *result, Expression *left, Expression *right, Register *reg)
{   // Reminder: dividend / divisor
    // generate left and right side
    left->generate();
    right->generate();

    // load left side (dividend)
    load(left, eax);

    // Unload edx
    load(nullptr, edx);

    unsigned value = 0; // fake value to pass to isNumber

    // Load right into ecx if it is a number (immediate) bc instruction does not allow div by immediate
    if (right->isNumber(value))
        load(right, ecx);

    // Sign extend eax into edx (64-bit dividend)
    cout << "\tcltd\t" << endl;
    // Perform operation - register is ecx if divisor is immediate or something else if not immediate
    cout << "\tidivl\t" << right << endl;

    // Unassign left and right register
    assign(left, nullptr);
    assign(right, nullptr);

    // Assign result to correct register
    // Going to pass eax or edx from caller Divide or Remainder functions when calling this function
    // Divide - going to pass eax into reg parameter
    // Remainder - going to pass edx into reg parameter
    assign(result, reg);
}

void Divide::generate()
{
    divide(this, _left, _right, eax);
}

void Remainder::generate()
{
    divide(this, _left, _right, edx);
}

static void compare(Expression *result, Expression *left, Expression *right, const string &opcode)
{
    // generate left and right side
    left->generate();
    right->generate();

    // load left if not loaded
    if (left->_register == nullptr)
        load(left, getreg());

    // Compare left and right
    cout << "\tcmpl\t" << right << ", " << left << endl;

    // Unassign left and right register
    assign(left, nullptr);
    assign(right, nullptr);

    // Assign result to a register
    assign(result, getreg());

    // Store result of condition code in byte register
    cout << "\t" << opcode << "\t" << result->_register->byte() << endl;

    // Zero-extend byte to long
    cout << "\tmovzbl\t" << result->_register->byte() << ", " << result->_register << endl;
}

void LessThan::generate()
{
    compare(this, _left, _right, "setl");
}

void GreaterThan::generate()
{
    compare(this, _left, _right, "setg");
}

void LessOrEqual::generate()
{
    compare(this, _left, _right, "setle");
}

void GreaterOrEqual::generate()
{
    compare(this, _left, _right, "setge");
}

void Equal::generate()
{
    compare(this, _left, _right, "sete");
}

void NotEqual::generate()
{
    compare(this, _left, _right, "setne");
}

void Cast::generate()
{
    _expr->generate();

    // if register is unallocated
    if (_expr->_register == nullptr)
        load(_expr, getreg());

    if (_expr->type().size() == 1)
        cout << "\tmovsbl\t" << _expr << ", " << getreg() << endl;

    assign(this, _expr->_register);
}

void Not::generate()
{
    _expr->generate();

    // if register is unallocated
    if (_expr->_register == nullptr)
        load(_expr, getreg());

    // Perform operation
    cout << "\tcmpl\t"
         << "$0"
         << ", " << _expr << endl;
    cout << "\tsete\t" << _expr->_register->byte() << endl;
    // Note for below: the way cout is overloaded, you can call either
    //  _expr or _expr->_register, they both work!
    cout << "\tmovzbl\t" << _expr->_register->byte() << ", " << _expr->_register << endl;

    assign(this, _expr->_register);
}

void Negate::generate()
{
    _expr->generate();

    // if register is unallocated, load it
    if (_expr->_register == nullptr)
        load(_expr, getreg());

    // perform operation
    cout << "\tnegl\t" << _expr << endl;

    assign(this, _expr->_register);
}

void Return::generate()
{
    //Generate and load expression into eax
    _expr->generate();
    if(_expr->_register != eax)
        load(_expr, eax);

    //Jump to [function name].exit
    cout << "\tjmp\t" << funcname << ".exit" << endl;

    //Unassign expression
    assign(_expr, nullptr);
}

void Expression::test(const Label &label, bool ifTrue)
{
    generate();

    if(_register == nullptr)
        load(this, getreg());

    cout << "\tcmpl\t" << "$0" << ", " << this << endl;
    cout << (ifTrue ? "\tjne\t" : "\tje\t") << label << endl;

    assign(this, nullptr);
}

void LogicalOr::generate()
{
    Label true_label, exit_label;

    //Test left and right expressions
    _left->test(true_label, true);
    _right->test(true_label, true);

    //Jump to skip label
    cout << "\tjmp\t" << exit_label << endl;

    //assign and move 0/1 to current
    assign(this, getreg());

    //Write shortcircuit label, move 0/1 to current, write skiplabel
    cout << true_label << ":" << endl;
    cout << "\tmovl\t" << "$1" << ", " << this << endl;
    cout << exit_label << ":" << endl;
}

void LogicalAnd::generate()
{
    //Comments same as above
    Label false_label, exit_label;

    _left->test(false_label, false);

    _right->test(false_label, false);

    cout << "\tjmp\t" << exit_label << endl;

    assign(this, getreg());

    cout << false_label << ":" << endl;
    cout << "\tmovl\t" << "$0" << ", " << this << endl;
    cout << exit_label << ":" << endl;
}

void While::generate()
{   //From class

    Label loop, exit;

    cout << loop << ":" << endl;

    _expr->test(exit, false);
    _stmt->generate();

    cout << "\tjmp\t" << loop << endl;
    cout << exit << ":" << endl;
}

void For::generate()
{
    Label loop_label, exit_label;
    
    //Generate init
    _init->generate();

    //Enter loop
    cout << loop_label << ":" << endl;

    //Test expression
    _expr->test(exit_label, false);

    //Generate statement
    _stmt->generate();

    //Generate increment
    _incr->generate();

    //Jump to loop label
    cout << "\tjmp\t" << loop_label << endl;

    //Write exit label
    cout << exit_label << ":" << endl;
}

void If::generate()
{
    Label skip_label, exit_label;

    //Test the expression
    _expr->generate();
    cout << "\tcmp\t" << "$0" << ", " << _expr << endl;
    cout << "\tje\t" << skip_label << endl;

    assign(_expr, nullptr);

    //Generate then statement
    _thenStmt->generate();

    //Check if there is an else statement
    if(_elseStmt == nullptr)
        cout << skip_label << ":" << endl;
    else
    {
        //Jump to end label
        cout << "\tjmp\t" << exit_label << endl;
        //Write else label
        cout << skip_label << ":" << endl;
        //Generate else statement
        _elseStmt->generate();
    }

    //Write end label
    cout << exit_label << ":" << endl;
}

void Dereference::generate()
{
    _expr->generate();

    // if register is unallocated, load it
    if (_expr->_register == nullptr)
        load(_expr, getreg());

    // Move value at dereferenced ptr location to result register
    cout << (_expr->type().deref().size() == 1 ? "\tmovb\t" : "\tmovl\t");
    cout << "(" << _expr << ")"
         << ", " << _expr << endl;

    assign(this, _expr->_register);
}

void Address::generate()
{
    int offset;
    Expression *base;
    Expression *ptr;

    findBaseAndOffset(_expr, base, offset);

    if (base->isDereference(ptr))
    {
        ptr->generate();

        // if register is unallocated, load it
        if (ptr->_register == nullptr)
            load(ptr, getreg());

        assign(this, ptr->_register);

        cout << "\taddl\t" << "$" << offset << ", " << this << endl;
    }
    else
    {
        assign(this, getreg());
        // load address of operand and store in result's register
        cout << "\tleal\t" << offset << "+" << base << ", " << this << endl;
    }
}

void Field::generate()
{
    int offset;

    Expression *base;
    Expression *ptr; //just pass something to isDereference

    findBaseAndOffset(this, base, offset);

    if(base->isDereference(ptr))
    {
        ptr->generate();

        if(ptr->_register == nullptr)
            load(ptr, getreg());
        
        //assign resulting expression to register
        assign(this, getreg());

        //Move value at dereferenced ptr location to result register
        if(ptr->type().size() == 4)
             cout << "\tmovl\t" << offset << "(" << ptr << ")" << ", " << this << endl;
        else
            cout << "\tmovb\t" << offset << "(" << ptr << ")" << ", " << this << endl;
    }
    else
    {
        //assign resulting expression to register
        assign(this, getreg());

        //Move base to result register
        if(this->type().size() == 4)
             cout << "\tmovl\t" << offset << "+" << base << ", " << this << endl;
        else
            cout << "\tmovb\t" << offset << "+" << base->_register->byte() << ", " << this << endl;
    }
}

void String::operand(ostream &ostr) const
{
    if (strings.count(_value) <= 0)
        strings[_value] = new Label();

    ostr << *(strings[_value]);
}