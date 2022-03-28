# ifndef TYPE_H
# define TYPE_H
# include <string>
# include <vector>
# include <ostream>
# include <cassert>

enum {ARRAY, CALLBACK, ERROR, FUNCTION, SCALAR}; //declarator (specifier kind)

typedef std::vector<class Type> Parameters; //vector(list) of class Type objects(ptrs) for function parameters

class Type 
{
    typedef std::string string;
    /*private by default*/
    int _kind;
    string _specifier;
    unsigned _indirection;

    unsigned _length; //array length
    Parameters *_parameters; //list of function parameters

    public:
        Type(int kind, const string &specifier, unsigned indirection); //constructor declaration
        Type(); //default constructor

        //Accessors
        const string &specifier() const 
        {
            return _specifier;
        }
        unsigned indirection() const 
        {
            return _indirection;
        }
        unsigned length() const
        {
            assert(_kind == ARRAY);
            return _length;
        }
        Parameters *parameters() const
        {
            return _parameters;
        }

        //Boolean checkers
        bool isArray() const
        {
            return _kind == ARRAY;
        }
        bool isCallback() const
        {
            return _kind == CALLBACK;
        }
        bool isError() const
        {
            return _kind == ERROR;
        }
        bool isFunction() const
        {
            return _kind == FUNCTION;
        }
        bool isScalar() const
        {
            return _kind == SCALAR;
        }

        //Mutators
        void length(unsigned len)
        {
            _length = len;
        }
        void parameters(Parameters *params)
        {
            _parameters = params;
        }

        //Operator overloading
        // x == y --> x.operator==(y)
        bool operator ==(const Type &rhs) const;
        bool operator !=(const Type &rhs) const;

        bool isStruct() const;
};

//<< operator overloading
std::ostream &operator <<(std::ostream &ostr, const Type &type);

# endif /* TYPE_H */