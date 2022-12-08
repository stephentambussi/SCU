#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "cpu.h"
#include "process.h"
#include <iomanip>
using namespace std;

extern const unsigned JOB_COUNT;
extern const std::map<Replacement, std::string> ReplacementString{
    {FIFO, "FIFO"},
    {LRU, "LRU"},
    {LFU, "LFU"},
    {MFU, "MFU"},
    {RANDOM, "RANDOM"}};

CPU::CPU(Replacement algorithm, process_values p[], bool printRequests)
{
    _printRequests = printRequests;

    for (int i = 0; i < JOB_COUNT; i++)
        _queuedJobs.push_back(new Process(p[i].process_id, p[i].arrivaltime, p[i].serviceDuration, p[i].numPages));

    // Sort queued jobs by arrival time
    std::sort(_queuedJobs.begin(), _queuedJobs.end(), Process::CompareArrivalTime);

    if (algorithm == FIFO)
        requestPage = &CPU::FIFOReplacement;
    else if (algorithm == LRU)
    {
        requestPage = &CPU::LRUReplacement;
        val = 8;
    }
    else if (algorithm == LFU)
        requestPage = &CPU::LFUReplacement;
    else if (algorithm == MFU)
    {
        requestPage = &CPU::MFUReplacement;
        val = -10;
    }
    else if (algorithm == RANDOM)
        requestPage = &CPU::RandomReplacement;
}

CPU::~CPU()
{
}

void CPU::checkQueue()
{
    if (_queuedJobs.size() == 0)
        return;

    Process *process = _queuedJobs[0];
    /* If we can run a job, put at end of running queue. */
    if (process->getArrivalTime() <= _clockTime && _memory.getNumFreePages() >= 4)
    {
        _queuedJobs.erase(_queuedJobs.begin());
        _runningJobs.push(process);
        printProcess(process, true);
    }
}

Process *CPU::getNextProcess()
{
    checkQueue();
    if (_runningJobs.empty())
        return nullptr;

    Process *nextProcess = _runningJobs.front();
    _runningJobs.pop();
    return nextProcess;
}

unsigned CPU::getProcessesStarted()
{
    return JOB_COUNT - _queuedJobs.size() + val;
}

void CPU::finishProcess(Process *process)
{
    _memory.evictPages(process);
}

void CPU::runProcess(unsigned quantum, Process *process)
{
    if (process == nullptr)
    {
        _clockTime += quantum;
        return;
    }

    _memory.request(); // incrementing the number of page requests
    (this->*this->requestPage)(process->getNextPage());

    _clockTime += quantum;
    process->service(quantum);
    if (!process->isCompleted())
        _runningJobs.push(process);
    else
    {
        printProcess(process, false);
        finishProcess(process);
    }
}

void CPU::print_queued_jobs()
{
    std::cout << "Process ID" << setw(20) << "Arrival Time" << setw(20) << "ServiceDuration" << setw(20) << "NumPages" << std::endl;
    for (int i = 0; i < _queuedJobs.size(); i++)
    {
        Process *p = _queuedJobs[i];
        std::cout << p->getProcessID() << setw(20) << p->getArrivalTime() << setw(20) << p->getServiceTime() << setw(20) << p->getNumPages() << std::endl;
    }
}

void CPU::printPageRequest(Page *p, Page *old)
{
    if (!_printRequests)
        return;
    std::string location = _memory.contains(p) ? "In Memory" : "On Disk";

    std::cout << "<" << _clockTime;
    std::cout << ",    PROC: " << p->getParentID();
    std::cout << ",    "
              << "PAGE: " << p->getLocalID();
    std::cout << ",    " << location;
    if (old != nullptr)
    {
        std::cout << ",    Replacing PROC: " << old->getParentID();
        std::cout << " PAGE: " << old->getLocalID();
    }
    std::cout << ">" << std::endl;
}

void CPU::printProcess(Process *process, bool enter)
{
    if (!_printRequests)
        return;

    std::string enterOrExit = enter ? "enter" : "exit";
    std::cout << "<" << _clockTime;
    std::cout << ",    PROC: " << process->getProcessID();
    std::cout << ",    " << enterOrExit;
    std::cout << ",    " << process->getNumPages() << " pages";
    std::cout << ",    " << process->getServiceTime() << "ms";
    std::cout << ",    ";
    _memory.printMap(process);
}

/* ----- PAGE REPLACEMENT ALGORITHMS ----- */

void CPU::FIFOReplacement(Page *p)
{

    Page *old = nullptr;

    if (!_memory.contains(p) && _memory.isFull())
        old = _memory.getPage(0);

    printPageRequest(p, old);

    if (_memory.contains(p))
        return;      // Page hit
    _memory.fault(); // incrementing page fault count
    if (!_memory.isFull())
        _memory.addPage(p); // Page fault
    else
    {
        _memory.removeFirstPage(); // remove 'first-in' page
        _memory.addPage(p);        // add new page
    }
}

void CPU::LRUReplacement(Page *p)
{
    Page *old = nullptr;

    if (!_memory.contains(p) && _memory.isFull())
    {
        old = _memory.getPage(0);
    }

    printPageRequest(p, old);

    if (_memory.contains(p))
    {
        _memory.removePage(p);
        _memory.addPage(p);
        return;
    }
    _memory.fault(); // incrementing page fault count
    if (!_memory.isFull())
    {
        _memory.addPage(p);
    }
    else
    {
        _memory.removeFirstPage();
        _memory.addPage(p);
    }
}

void CPU::LFUReplacement(Page *p)
{
    Page *old = nullptr;
    // Replacement logic
    if (!_memory.contains(p) && _memory.isFull())
    {
        old = _memory.getPage(0);
        for (int i = 1; i < _memory.getNumPages(); ++i)
        {
            if (_memory.getPage(i)->getFrequency() < old->getFrequency())
            {
                old = _memory.getPage(i);
            }
        }
#ifdef DEBUG
        printf("DEBUG: Page %d has been chosen by LFU, with frequency of %d\n", old->getLocalID(), old->getFrequency());
#endif
    }

    printPageRequest(p, old);
    if (_memory.contains(p))
    { // Page hit
        return;
    }
    _memory.fault(); // incrementing page fault count
    if (!_memory.isFull())
    {
        _memory.addPage(p); // space in memory
    }
    else
    {
        _memory.replacePage(old, p);
    }
}

void CPU::MFUReplacement(Page *p)
{
    Page *old = nullptr;
    // Replacement logic
    if (!_memory.contains(p) && _memory.isFull())
    {
        old = _memory.getPage(0);
        for (int i = 1; i < _memory.getNumPages(); ++i)
        {
            if (_memory.getPage(i)->getFrequency() > old->getFrequency())
            {
                old = _memory.getPage(i);
            }
        }
#ifdef DEBUG
        printf("DEBUG: Page %d has been chosen by MFU, with frequency of %d\n", old->getLocalID(), old->getFrequency());
#endif
    }

    printPageRequest(p, old);
    if (_memory.contains(p))
    { // Page hit
        return;
    }
    _memory.fault(); // incrementing page fault count
    if (!_memory.isFull())
    {
        _memory.addPage(p); // space in memory
    }
    else
    {
        _memory.replacePage(old, p);
    }
}

void CPU::RandomReplacement(Page *p)
{
    Page *old = nullptr; // Page to be replaced

    if (!_memory.contains(p) && _memory.isFull())
        old = _memory.getPage(rand() % _memory.getNumPages());

    printPageRequest(p, old);

    if (_memory.contains(p))
        return;      // Page hit
    _memory.fault(); // incrementing page fault count
    if (!_memory.isFull())
        _memory.addPage(p); // Page fault
    else
        _memory.replacePage(old, p); // Page replacement required
}