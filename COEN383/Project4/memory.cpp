#include <cassert>
#include <iostream>
#include "memory.h"
#include "page.h"

void Memory::addPage(Page *p)
{
    assert(!isFull());

    _memory.push_back(p);
}

void Memory::evictPages(Process *process)
{
    unsigned pId = process->getProcessID();
    for (unsigned i = 0; i < _memory.size(); i++)
    {
        if (pId == _memory[i]->getParentID())
        {
            _memory.erase(_memory.begin() + i);
            evictPages(process);
            return;
        }
    }
}

void Memory::replacePage(Page *oldPage, Page *newPage)
{
    for (unsigned i = 0; i < _memory.size(); i++)
        if (_memory[i] == oldPage)
            _memory[i] = newPage;
}

void Memory::removePage(Page *oldPage)
{
    for (unsigned i = 0; i < _memory.size(); i++)
    {
        if (_memory[i] == oldPage)
        {
            _memory.erase(_memory.begin() + i);
            return;
        }
    }
}

void Memory::printMap(Process *process)
{
    unsigned pId = process->getProcessID();

    std::cout << "<";
    for (unsigned i = 0; i < _memory.size(); i++)
    {
        if (pId != _memory[i]->getParentID())
            std::cout << _memory[i]->getParentID();
        else
            std::cout << ".";
        if (i != 99)
            std::cout << " ";
    }

    for (unsigned i = _memory.size(); i < 100; i++)
    {
        std::cout << ".";
        if (i != 99)
            std::cout << " ";
    }
    std::cout << ">" << std::endl;
}