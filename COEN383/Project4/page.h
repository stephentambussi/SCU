#ifndef PAGE_H
#define PAGE_H
#include <vector>
#include <ostream>

class Page
{
    unsigned _globalID, _localID, _parentID, _frequency, _lastAccessTime;

public:
    Page(unsigned parentID, unsigned localID);

    unsigned getGlobalID() { return _globalID; }
    unsigned getLocalID() { return _localID; }
    unsigned getParentID() { return _parentID; }
    unsigned getFrequency() { return _frequency; }
    unsigned getAccessTime() { return _lastAccessTime; }

    void incrementFrequency() { ++this->_frequency; }
    void setAccessTime(unsigned t) { this->_lastAccessTime = t; }
};

#endif /* PAGE_H */