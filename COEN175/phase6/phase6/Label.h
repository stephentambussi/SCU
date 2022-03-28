/*	Stephen Tambussi - 3/11/22
	COEN175 - Phase 6: Code Generation
*/

# ifndef LABEL_H
# define LABEL_H
# include <ostream>

class Label 
{
    static unsigned _counter;
    unsigned _number;

public:
    Label();
    unsigned number() const;
};

std::ostream &operator <<(std::ostream &ostr, const Label &label);

# endif /* LABEL_H */
