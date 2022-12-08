#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "process.h"

extern const unsigned RUN_TIME;
static unsigned id = 0;

Process::Process() : _processID(id++)
{
    _arrivalTime = rand() % RUN_TIME;
    _serviceDuration = (rand() % 5 + 1) * 1000;
    allocatePages();
}

Process::Process(unsigned pid, unsigned at, unsigned sd, unsigned np)
{
    _processID = pid;
    _arrivalTime = at;
    _serviceDuration = sd;
    _numpages = np;
    allocatePages(_numpages);
}

Process::~Process()
{
    for (unsigned i = 0; i < _pages.size(); i++)
        delete _pages[i];
    delete this;
}

void Process::allocatePages(unsigned np)
{
    for (int i = 0; i < np; i++)
        _pages.push_back(new Page(i, _processID));
}

void Process::allocatePages()
{
    unsigned numPages = rand() % 4;
    if (numPages == 0)
        numPages = 5;
    else if (numPages == 1)
        numPages = 11;
    else if (numPages == 2)
        numPages = 17;
    else if (numPages == 3)
        numPages = 31;

    for (int i = 0; i < numPages; i++)
        _pages.push_back(new Page(i, _processID));
}

Page *Process::getNextPage()
{
    int delta_i;
    unsigned branch = rand() % 10 + 1;

    // get local page id
    if (branch <= 7)
    {
        delta_i = rand() % 3;
        if (delta_i == 2)
            delta_i = -1;
    }
    else
        delta_i = rand() % getNumPages();

    // keeping track of page's local id
    if (_lastReferencedPage == -1)
        _lastReferencedPage = 0;
    else
        _lastReferencedPage = (_lastReferencedPage + delta_i) % getNumPages();

    // increment page frequency
    _pages[_lastReferencedPage]->incrementFrequency();

    // return global page id
    return _pages[_lastReferencedPage];
}

void Process::service(unsigned quantum)
{
    _timeRun += quantum;
}

bool Process::CompareArrivalTime(const Process *left, const Process *right)
{
    return left->getArrivalTime() < right->getArrivalTime();
}