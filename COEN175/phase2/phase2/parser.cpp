//Stephen Tambussi - 1/23/22
//COEN175 - Phase 2: Syntax Analysis
# include <iostream>
# include "lexer.h"
# include "tokens.h"

using namespace std;

int lookahead;
string lexbuf;
//have to declare bc definition is below a function that calls it
void expression(); 
void expression_list();
int specifier();
void pointers();
void statement();
void declarations();

static void error()
{
    if(lookahead == DONE)
        report("ERROR: incorrect syntax at end of file");
    else
        report("ERROR: incorrect syntax at '%s'", lexbuf);
    
    exit(EXIT_FAILURE);
}

static void match(int t)
{
    if(lookahead != t)
        error();
    lookahead = lexan(lexbuf);
}

bool isSpecifier(int t)
{
    if(t == INT || t == CHAR || t == STRUCT)
        return true;
    else return false;
}

//Parsing Expressions
void primary_expression(bool lp)
{
    if(lp)
    {
        expression();
        match(')');
    }
    else if(lookahead == ID)
        match(ID);
    else if(lookahead == CHARACTER)
        match(CHARACTER);
    else if(lookahead == STRING)
        match(STRING);
    else if(lookahead == NUM)
        match(NUM);
    return;
}

void postfix_expression(bool lp)
{
    primary_expression(lp); 
    while(1)
    {
        if(lookahead == LBRACK)
        {
            match('[');
            expression();
            match(']');
            cout << "index" << endl;
        }
        else if(lookahead == LPAREN)
        {
            match('(');

            if(lookahead != RPAREN)
                expression_list();

            match(')');
            cout << "call" << endl;
        }
        else if(lookahead == DOT)
        {
            match('.');
            match(ID);
            cout << "dot" << endl;
        }
        else if(lookahead == ARROW)
        {
            match(ARROW);
            match(ID);
            cout << "arrow" << endl;
        }
        else break;
    }
    return;
}

void prefix_expression()
{
    if(lookahead == NOT)
    {
        match('!');
        prefix_expression();
        cout << "not" << endl;
    }
    else if(lookahead == MINUS)
    {
        match('-');
        prefix_expression();
        cout << "neg" << endl;
    }
    else if(lookahead == STAR)
    {
        match('*');
        prefix_expression();
        cout << "deref" << endl;
    }
    else if(lookahead == ADDR)
    {
        match('&');
        prefix_expression();
        cout << "addr" << endl;
    }
    else if(lookahead == SIZEOF)
    {
        match(SIZEOF);
        if(lookahead == LPAREN)
        {
            match('(');
            if(isSpecifier(lookahead))
            {
                specifier();
                pointers();
            }
            else
                postfix_expression(true);
        }
        else
            prefix_expression();
        cout << "sizeof" << endl;
    }
    else if(lookahead == LPAREN)
    {
        match('(');
        if(isSpecifier(lookahead))
        {
            specifier();
            pointers();
            match(')');
            prefix_expression();
            cout << "cast" << endl;
        }
        else
            postfix_expression(true);
    }
    else
        postfix_expression(false);
    return;
}

void multiplicative_expression()
{
    prefix_expression();
    while(1)
    {
        if(lookahead == STAR)
        {
            match('*');
            prefix_expression();
            cout << "mul" << endl;
        }
        else if(lookahead == DIV)
        {
            match('/');
            prefix_expression();
            cout << "div" << endl;
        }
        else if(lookahead == REM)
        {
            match('%');
            prefix_expression();
            cout << "rem" << endl;
        }
        else break;
    }
    return;
}

void additive_expression()
{
    multiplicative_expression();
    while(1)
    {
        if(lookahead == PLUS)
        {
            match('+');
            multiplicative_expression();
            cout << "add" << endl;
        }
        else if(lookahead == MINUS)
        {
            match('-');
            multiplicative_expression();
            cout << "sub" << endl;
        }
        else break;
    }
    return;
}

void relational_expression()
{
    additive_expression();
    while(1)
    {
        if(lookahead == LTN)
        {
            match('<');
            additive_expression();
            cout << "ltn" << endl;
        }
        else if(lookahead == GTN)
        {
            match('>');
            additive_expression();
            cout << "gtn" << endl;
        }
        else if(lookahead == LEQ)
        {
            match(LEQ);
            additive_expression();
            cout << "leq" << endl;
        }
        else if(lookahead == GEQ)
        {
            match(GEQ);
            additive_expression();
            cout << "geq" << endl;
        }
        else break;
    }
    return;
}

void equality_expression()
{
    relational_expression();
    while(1)
    {
        if(lookahead == EQL)
        {
            match(EQL);
            relational_expression();
            cout << "eql" << endl;
        }
        else if(lookahead == NEQ)
        {
            match(NEQ);
            relational_expression();
            cout << "neq" << endl;
        }
        else break;
    }
    return;
}

void logical_and_expression()
{
    equality_expression();
    while(lookahead == AND)
    {
        match(AND);
        equality_expression();
        cout << "and" << endl;
    }
    return;
}

void expression()
{
    logical_and_expression();
    while(lookahead == OR)
    {
        match(OR);
        logical_and_expression();
        cout << "or" << endl;
    }
    return;
}

void expression_list() 
{
    expression();
    while(lookahead == COMMA)
    {
        match(',');
        expression();
    }
    return;
}

void assignment() 
{
    expression();
    if(lookahead == ASSIGN)
    {
        match('=');
        expression();
    }
    return;
}

void statements()
{
    while(lookahead != RBRACE)
    {
        statement();
    }
    return;
}

void statement()
{
    if(lookahead == LBRACE)
    {
        match('{');
        declarations();
        statements();
        match('}');
    }
    else if(lookahead == RETURN) //return statement
    {
        match(RETURN);
        expression();
        match(';');
    }
    else if(lookahead == WHILE) //while-loop
    {
        match(WHILE);
        match('(');
        expression();
        match(')');
        statement();
    }
    else if(lookahead == FOR) //for-loop
    {
        match(FOR);
        match('(');
        assignment();
        match(';');
        expression();
        match(';');
        assignment();
        match(')');
        statement();
    }
    else if(lookahead == IF) //if-statement
    {
        match(IF);
        match('(');
        expression();
        match(')');
        statement();
        if(lookahead == ELSE)
        {
            match(ELSE);
            statement();
        }
    }
    else
    {
        assignment();
        match(';');
    }
    return;
}

void pointers()
{
    while(lookahead == STAR)
    {
        match('*');
    }
    return;
}

int specifier()
{
    if(isSpecifier(lookahead))
    {
        int type = lookahead;
        match(lookahead);
        if(type == STRUCT)
            match(ID);
        return type;
    }
    else
    {
        error();
        return 0;
    }
}

void declarator()
{
    pointers();
    if(lookahead == ID)
    {
        match(ID);
        if(lookahead == LBRACK)
        {
            match('[');
            match(NUM);
            match(']');
        }
    }
    else if(lookahead == LPAREN)
    {
        match('(');
        match('*');
        match(ID);
        match(')');
        match('(');
        match(')');
    }
    return;
}

void declarator_list()
{
    declarator();
    while(lookahead == COMMA)
    {
        match(',');
        declarator();
    }
    return;
}

void declaration()
{
    specifier();
    declarator_list();
    match(';');
    return;
}

void declarations()
{
    while(isSpecifier(lookahead))
        declaration();
    return;
}

void parameter()
{
    specifier();
    pointers();
    if(lookahead == ID)
    {
        match(ID);
    }
    else if(lookahead == LPAREN)
    {
        match('(');
        match('*');
        match(ID);
        match(')');
        match('(');
        match(')');
    }
    return;
}

void parameter_list()
{
    parameter();
    while(lookahead == COMMA)
    {
        match(',');
        parameter();
    }
    return;
}

void parameters()
{
    if(lookahead == VOID)
        match(VOID);
    else
        parameter_list();
    return;
}

void global_declarator()
{
    pointers();
    if(lookahead == ID)
    {
        match(ID);
        if(lookahead == LPAREN)
        {
            match('(');
            match(')');
        }
        else if(lookahead == LBRACK)
        {
            match('[');
            match(NUM);
            match(']');
        }
    }
    else if(lookahead == LPAREN)
    {
        match('(');
        match('*');
        match(ID);
        match(')');
        match('(');
        match(')');
    }
    return;
}

void remaining_declarators()
{
    while(lookahead == COMMA)
    {
        match(',');
        global_declarator();
    }
    match(';');
    return;
}

void function_or_global()
{
    if(specifier() == STRUCT && lookahead == LBRACE) //type-def
    {
        match('{');
        declaration();
        declarations();
        match('}');
        match(';');
    }
    else
    {
        pointers(); 
        if(lookahead == LPAREN) //function pointer
        {
            match('(');
            match('*');
            match(ID);
            match(')');
            match('(');
            match(')');
            remaining_declarators();
        }
        else
        {
            match(ID);

            if(lookahead == LPAREN)
            {
                match('(');
                if(lookahead != RPAREN) //function definition
                {
                    parameters();
                    match(')');
                    match('{');
                    declarations();
                    statements();
                    match('}');
                }
                else //function declaration
                {
                    match(')');
                    remaining_declarators();
                }
            }

            else if(lookahead == LBRACK) //array declaration
            {
                match('[');
                match(NUM);
                match(']');
                remaining_declarators();
            }
            
            else
                remaining_declarators();
        }
    }
    return;
}

int main()
{
    lookahead = lexan(lexbuf);

    while(lookahead != DONE)
    {
        function_or_global();
        //Testing below
        //expression();
        //statement();
        //declaration();
    }

    exit(EXIT_SUCCESS);
}