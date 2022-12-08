#ifndef CPU_H
#define CPU_H
#include <map>
#include <vector>
#include <queue>
#include "memory.h"
#include "process.h"
#include "page.h"

enum Replacement
{
    FIFO,
    LRU,
    LFU,
    MFU,
    RANDOM
};
extern const std::map<Replacement, std::string> ReplacementString;

class CPU
{
    unsigned _clockTime = 0, val = 0;
    bool _atJobCapacity = false, _printRequests;

    std::vector<Process *> _queuedJobs; /* processes waiting to be run. */
    std::queue<Process *> _runningJobs; /* processes currently being run. */
    Memory _memory;

    /* Function pointer for one of the 5 page replacement algorithms */
    void (CPU::*requestPage)(Page *p);
    void FIFOReplacement(Page *p);
    void LRUReplacement(Page *p);
    void LFUReplacement(Page *p);
    void MFUReplacement(Page *p);
    void RandomReplacement(Page *p);

    void checkQueue();
    void finishProcess(Process *process);
    void printPageRequest(Page *p, Page *old);
    void printProcess(Process *process, bool enter);

public:
    CPU(Replacement algorithm, process_values p[], bool printRequests = false);
    ~CPU();

    bool isProcessesComplete()
    {
        return _queuedJobs.empty() && _runningJobs.empty();
    }
    unsigned getClockTime() { return _clockTime; }
    Process *getNextProcess();
    double getRatio() { return _memory.ratio(); }
    unsigned getProcessesStarted();

    void runProcess(unsigned quantum, Process *process);
    void print_queued_jobs();

    int getRequests() { return _memory.getmr(); }
    int getFaults() { return _memory.getmf(); }
};

#endif /* CPU_H */