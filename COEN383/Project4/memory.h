#ifndef MEMORY_H
#define MEMORY_H
#include <algorithm>
#include <deque>
#include "page.h"
#include "process.h"

extern const unsigned NUM_PAGES;

class Memory
{
    int _requests = 0, _faults = 0;
    std::deque<Page *> _memory;

public:
    bool isEmpty() { return _memory.empty(); }
    bool isFull() { return _memory.size() >= NUM_PAGES; }

    unsigned getNumFreePages() { return NUM_PAGES - _memory.size(); }
    unsigned getNumPages() { return _memory.size(); }
    Page *getPage(unsigned index) { return _memory[index]; }

    void addPage(Page *p);
    bool contains(const Page *page)
    {
        return std::find(_memory.begin(), _memory.end(), page) != _memory.end();
    }
    void evictPages(Process *process);
    void replacePage(Page *oldPage, Page *newPage);
    void removePage(Page *oldPage);
    void removeFirstPage() { _memory.pop_front(); }
    void printMap(Process *process = nullptr);

    void fault() { _faults++; }
    void request() { _requests++; }
    double ratio() { return 1.0 * (_requests - _faults) / _requests; }
    int getmr() { return _requests; }
    int getmf() { return _faults; }
};

#endif /* MEMORY_H */