# include "page.h"

static unsigned _globalIDCounter = 0;

Page::Page(unsigned localID, unsigned parentID)
        : _globalID(_globalIDCounter++), _localID(localID), _parentID(parentID) { _frequency=0;}