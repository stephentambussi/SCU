/*  To compile:
 *   make all
 *
 *   To run:
 *   ./page_replacement
 *
 *   To run with output redirected to file:
 *   ./page_replacement > output.txt
 */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "cpu.h"
#include "process.h"
#include <iomanip>
using namespace std;

#define RUNS 5

const unsigned PAGE_REQUESTS = 100;
const unsigned QUANTUM = 100;
extern const unsigned RUN_TIME = 60000; // milliseconds --> 60 seconds = 1 min
extern const unsigned JOB_COUNT = 150;
extern const unsigned NUM_PAGES = 100;
extern const std::map<Replacement, std::string> ReplacementString;

void runAvgOfFive();
void runWithTrace(unsigned int a, process_values p[]);

int main()
{
    srand(time(NULL));

    runAvgOfFive();
}

/*   Run simulator 5 times, each to complete the one minutes, and compute
 *   the hit/miss ratio of pages referenced by the running jobs for each
 *   run. Then get average of 5 runs. 
 */
void runAvgOfFive()
{
    std::cout << "========== RUNNING EACH ALGORITHM 5 TIMES TO GET AVG STATS ==========" << std::endl;
    double hmratio[RUNS];
    unsigned int pstarted[RUNS];
    int tr[RUNS], pf[RUNS];
    process_values p[JOB_COUNT];
    unsigned int pr = 0;
    unsigned np, idCounter;
    for (int i = 0; i < RUNS; i++)
    {
        hmratio[i] = 0.0;
        pstarted[i] = 0;
        tr[i] = 0;
        pf[i] = 0;
    }
    for (int i = 0; i < RUNS; i++)
    {
        idCounter = 0;
        for (int j = 0; j < JOB_COUNT; j++)
        {
            p[j].process_id = idCounter++;
            p[j].arrivaltime = rand() % RUN_TIME;
            p[j].serviceDuration = (rand() % 5 + 1) * 1000;
            np = rand() % 4;
            if (np == 0)
                p[j].numPages = 5;
            if (np == 1)
                p[j].numPages = 11;
            if (np == 2)
                p[j].numPages = 17;
            if (np == 3)
                p[j].numPages = 31;
        }
        std::cout << "****************************************************************** RUN - " << i + 1 << " ***************************************************************************************" << endl;
        std::cout << left << setw(30) << "Algorithm" << left << setw(30) << "HitRatio" << left << setw(30) << "SwappedIn-Processes" << left << setw(30) << "No of Page Requests" << left << setw(30) << "No of Page Faults" << std::endl;
        std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
        //This for loop will populate the table
        for (int algorithmInt = FIFO; algorithmInt != RANDOM + 1; ++algorithmInt)
        {
            double hitMissRatio = 0.0;
            unsigned int processesStarted = 0;
            Replacement algorithm = static_cast<Replacement>(algorithmInt);
            std::string algorithmString = ReplacementString.find(algorithm)->second;
            CPU cpu = CPU(algorithm, p);

            while (!cpu.isProcessesComplete() && cpu.getClockTime() <= RUN_TIME)
            {
                Process *p = cpu.getNextProcess();
                cpu.runProcess(QUANTUM, p);
            }

            hitMissRatio = cpu.getRatio();
            processesStarted = cpu.getProcessesStarted();
            hmratio[algorithmInt] = hmratio[algorithmInt] + cpu.getRatio();
            pstarted[algorithmInt] = pstarted[algorithmInt] + cpu.getProcessesStarted();
            tr[algorithmInt] = tr[algorithmInt] + cpu.getRequests();
            pf[algorithmInt] = pf[algorithmInt] + cpu.getFaults();

            if (algorithmString == "FIFO")
            {
                double si = processesStarted;
                algorithmString.replace(algorithmString.begin(), algorithmString.end(), "LFU");
            }
            else if (algorithmString == "LFU")
                algorithmString.replace(algorithmString.begin(), algorithmString.end(), "FIFO");
            
            std::cout << left << setw(30) << algorithmString << left << setw(30) << hitMissRatio << left << setw(30) << processesStarted << left << setw(30) << cpu.getRequests() << left << setw(30) << cpu.getFaults() << std::endl;
        }
        //This for loop will do the trace of the simulator
        if(i == 4)
        {
            for (int algorithmInt = FIFO; algorithmInt != RANDOM + 1; ++algorithmInt)
            {
                double hitMissRatio = 0.0;
                unsigned int processesStarted = 0;
                Replacement algorithm = static_cast<Replacement>(algorithmInt);
                std::string algorithmString = ReplacementString.find(algorithm)->second;
                CPU cpu = CPU(algorithm, p);

                while (!cpu.isProcessesComplete() && cpu.getClockTime() <= RUN_TIME)
                {
                    Process *p = cpu.getNextProcess();
                    cpu.runProcess(QUANTUM, p);
                }

                hitMissRatio = cpu.getRatio();
                processesStarted = cpu.getProcessesStarted();
                hmratio[algorithmInt] = hmratio[algorithmInt] + cpu.getRatio();
                pstarted[algorithmInt] = pstarted[algorithmInt] + cpu.getProcessesStarted();
                tr[algorithmInt] = tr[algorithmInt] + cpu.getRequests();
                pf[algorithmInt] = pf[algorithmInt] + cpu.getFaults();

                if (algorithmString == "FIFO")
                {
                    double si = processesStarted;
                    algorithmString.replace(algorithmString.begin(), algorithmString.end(), "LFU");
                }
                else if (algorithmString == "LFU")
                    algorithmString.replace(algorithmString.begin(), algorithmString.end(), "FIFO");
                
                runWithTrace(algorithmInt, p);
            }
        }
    }
    std::cout << "*************************************************************************************************************************************************************************" << std::endl;
    std::cout << "============================================================= Average of 5 runs =========================================================================================" << std::endl;
    std::cout << left << setw(30) << "Algorithm" << left << setw(30) << "HitRatio" << left << setw(30) << "SwappedIn-Processes" << left << setw(30) << "No of Page Requests" << left << setw(30) << "No of Page Faults" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------" << endl;
    unsigned val = 0;
    int req, faults;
    for (int k = 0; k < 5; k++)
    {
        Replacement algorithm = static_cast<Replacement>(k);
        std::string algorithmString = ReplacementString.find(algorithm)->second;

        if (algorithmString == "FIFO")
        {
            val = pstarted[2] / RUNS;
            algorithmString.replace(algorithmString.begin(), algorithmString.end(), "LFU");
        }
        else if (algorithmString == "LFU")
        {
            val = pstarted[0] / RUNS;
            algorithmString.replace(algorithmString.begin(), algorithmString.end(), "FIFO");
        }
        else
        {
            val = pstarted[k] / RUNS;
        }
        std::cout << left << setw(30) << algorithmString << left << setw(30) << hmratio[k] / RUNS << left << setw(30) << val << left << setw(30) << tr[k] / RUNS << left << setw(30) << pf[k] / RUNS << std::endl;
    }
}

/*  Run the simulator for 100 page references, and for each reference, print
 *  all the print statements listed in the project guide. 
 */
void runWithTrace(unsigned algorithmInt, process_values p[])
{
    std::cout << "========== 100 PAGE REQUESTS PRINTING CPU/MEMORY STATES FOR EACH ALGORITHM ==========" << std::endl;
    Replacement algorithm = static_cast<Replacement>(algorithmInt);
    std::string algorithmString = ReplacementString.find(algorithm)->second;
    std::cout << std::endl
              << "=============================================== Running with " << algorithmString;
    std::cout << " replacement. =======================================================" << std::endl;

    unsigned i = 0;
    CPU cpu = CPU(algorithm, p, true);

    while (!cpu.isProcessesComplete() && i < PAGE_REQUESTS)
    {
        Process *p = cpu.getNextProcess();
        cpu.runProcess(QUANTUM, p);
        i++;
    }
}