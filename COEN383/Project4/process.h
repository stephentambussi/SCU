#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#include "page.h"

class Process
{
    unsigned _processID,
        _arrivalTime,
        _serviceDuration,
        _numpages = 0,
        _timeRun = 0;
    int _lastReferencedPage = -1;

    std::vector<Page *> _pages;

    void allocatePages();
    void allocatePages(unsigned np);

public:
    Process();
    Process(unsigned process_id, unsigned arrivaltime, unsigned serviceDuration, unsigned numPages);
    ~Process();

    unsigned getArrivalTime() const { return _arrivalTime; }
    Page *getNextPage();
    unsigned getNumPages() const { return _pages.size(); }
    unsigned getProcessID() const { return _processID; }
    unsigned getRemainingTime() const { return _serviceDuration - _timeRun; }
    unsigned getServiceTime() const { return _serviceDuration; }

    bool isCompleted() const { return _serviceDuration == _timeRun; }

    void service(unsigned quantum); // service process for specified process

    // static function used for sorting processes by arrival time
    static bool CompareArrivalTime(const Process *, const Process *);
};
struct process_values
{
    unsigned process_id,
        arrivaltime,
        serviceDuration,
        numPages;
};
#endif /* PROCESS_H */