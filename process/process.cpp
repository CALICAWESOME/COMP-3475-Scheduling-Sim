/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * process.cpp
 */
#include <sstream>
#include "process.h"

process::process(int arrivalTime, int burstTime, int priority) {
    this->pNo = numProc++;
    this->arrivalTime = arrivalTime;
    this->burstTime = burstTime;
    this->priority = priority;

    elapsed = 0;
    waitTime = 0;
}

// some getters
int process::getPNo() const {
    return pNo;
}
int process::getArrivalTime() const {
    return arrivalTime;
}
int process::getBurstTime() const {
    return burstTime;
}
int process::getPriority() const {
    return priority;
}
int process::getElapsed() const {
    return elapsed;
}
int process::getRemainingTime() const {
    return burstTime - elapsed;
}
int process::getWaitTime() const {
    return waitTime;
}
int process::getTurnaroundTime() const {
    return turnaroundTime;
}
// some setters and an incrementer
void process::incrementTimeElapsed() {
    elapsed++;
}
void process::setWaitTime(int waitTime) {
    process::waitTime = waitTime;
}
void process::setTurnaroundTime(int turnaroundTime) {
    process::turnaroundTime = turnaroundTime;
}

// string repr for process
string process::toString() {
    stringstream str;
    str << "== process " << pNo << " ==\n";
    str << "arr: " << arrivalTime << endl;
    str << "bst: " << burstTime << endl;
    str << "pri: " << priority << endl;
    str << "//\n";
    str << "awt: " << waitTime << endl;
    str << "tat: " << turnaroundTime << endl << endl;
    return str.str();
}
int process::numProc = 0;

process process::CPUIDLE = process(-1, -1, -1);

bool sortByArrivalTime(const process &p1, const process &p2) {
    if (p1.getArrivalTime() != p2.getArrivalTime())
        return p1.getArrivalTime() < p2.getArrivalTime();
    return p1.getPriority() < p2.getPriority();
}

bool sortByPNo(const process &p1, const process &p2) {
    return p1.getPNo() < p2.getPNo();
}

bool sortPointersByBurstTime(const process* p1, const process* p2) {
    if (p1->getBurstTime() != p2->getBurstTime())
        return p1->getBurstTime() < p2->getBurstTime();
    return p1->getPriority() < p2->getPriority();
}

bool sortPointersByRemainingTime(const process* p1, const process* p2) {
    if (p1->getRemainingTime() != p2->getRemainingTime())
        return p1->getRemainingTime() < p2->getRemainingTime();
    return p1->getPriority() < p2->getPriority();
}

bool sortPointersByPriority(const process* p1, const process* p2) {
    return p1->getPriority() < p2->getPriority();
}