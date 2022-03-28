/*	Stephen Tambussi - 3/11/22
	COEN175 - Phase 6: Code Generation
*/

# include "Label.h"

using namespace std;

unsigned Label::_counter = 0;

Label::Label() 
{
    _number = _counter++;
}

unsigned Label::number() const
{
    return _number;
}

ostream &operator <<(ostream &ostr, const Label &label)
{
    return ostr << ".L" << label.number();
}