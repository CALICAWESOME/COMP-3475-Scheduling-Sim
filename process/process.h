/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * process.h
 */
#ifndef PA_SCHEDULING_SIM_PROCESS_H
#define PA_SCHEDULING_SIM_PROCESS_H

#include <string>
using namespace std;

class process {
    // for setting pNo
    static int numProc;

    // generated values
    int pNo;
    int arrivalTime;
    int burstTime;
    int priority;

    // calculated values
    int elapsed;
    int waitTime;
    int turnaroundTime;

public:
    // ye constructor
    process(int, int, int);

    // some getters
    int getPNo() const;
    int getArrivalTime() const;
    int getBurstTime() const;
    int getPriority() const;
    int getElapsed() const;
    int getRemainingTime() const;
    int getWaitTime() const;
    int getTurnaroundTime() const;

    // setters & an incrementer
    void incrementTimeElapsed();
    void setWaitTime(int);
    void setTurnaroundTime(int);

    // string repr for process
    string toString();

    // CPUIDLE
    static process CPUIDLE;
};

bool sortByArrivalTime(const process&, const process&);
bool sortByPNo(const process&, const process&);
bool sortPointersByBurstTime(const process*, const process*);
bool sortPointersByRemainingTime(const process*, const process*);
bool sortPointersByPriority(const process*, const process*);

#endif //PA_SCHEDULING_SIM_PROCESS_H