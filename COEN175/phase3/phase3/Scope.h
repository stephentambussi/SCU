# ifndef SCOPE_H
# define SCOPE_H
# include "Symbol.h"
# include "Type.h"

typedef std::vector<Symbol *> Symbols; //declares vector(list) of Symbol ptrs type

class Scope
{
    typedef std::string string; //this is a workaround for not being able to open std namespace in .h files
    Scope *_enclosing;
    Symbols _symbols;

    public:
        //Constructor
        Scope(Scope *enclosing = nullptr);

        //Accessors
        Scope *enclosing() const
        {
            return _enclosing;
        }
        const Symbols &symbols() const
        {
            return _symbols;
        }

        //Operations
        void insert(Symbol *);
        void remove(const string &name);
        Symbol *find(const string &name) const;
        Symbol *lookup(const string &name) const;
};

# endif /* SCOPE_H */