/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * priority.cpp
 */
#include <algorithm>
#include <iostream>
#include <sstream>
#include "priority.h"

//////////////
// PRIORITY //
//////////////
vector<process> priority(vector<process> inputList, sillytui tui) {
    sort(inputList.rbegin(), inputList.rend(), sortByArrivalTime);

    stringstream message;

    process* currentProcess = &process::CPUIDLE;
    vector<process*> priorityQueue;
    vector<process> finished;

    // ye control loop!
    for (int time = 0, numProc = inputList.size(); finished.size() < numProc; time++) {
        // check for arriving processes (every time)
        while (!inputList.empty() && inputList.back().getArrivalTime() == time) {

            ///////////////////////////
            // PROCESSES ARRIVE HERE //
            ///////////////////////////

            // imHere = arriving process
            process* imHere = &inputList.back();
            // alert process arrival
            message << "P" << imHere->getPNo() << " arrived at t=" << time;
            tui.alert(message.str());
            // clear message
            message.str("");
            // if the arriving process has a higher priority than the current process
            if (imHere->getPriority() < currentProcess->getPriority()) {

                ////////////////////////////
                // PREMPTION HAPPENS HERE //
                ////////////////////////////
                // push current process on to queue
                priorityQueue.push_back(currentProcess);
                // alert premption
                message << "P" << currentProcess->getPNo() << " was prempted by P" << imHere->getPNo() << " at t=" << time;
                tui.alert(message.str());
                // clear message
                message.str("");
                // set CPU to idle
                currentProcess = &process::CPUIDLE;
            }
            // push arriving process to wait queue
            priorityQueue.push_back(imHere);
            // remove arriving process from input list
            inputList.pop_back();
            // reorder wait queue by priority
            sort(priorityQueue.begin(), priorityQueue.end(), sortPointersByPriority);
        }
        // if a process is running
        if (currentProcess != &process::CPUIDLE) {

            // if the process is finished, set CPU to idle.
            if (currentProcess->getElapsed() == currentProcess->getBurstTime()) {

                /////////////////////////////////////
                // A PROCESS FINISHES RUNNING HERE //
                /////////////////////////////////////

                // calculate turnaround time
                currentProcess->setTurnaroundTime(time - currentProcess->getArrivalTime());
                // calculate wait time
                currentProcess->setWaitTime(currentProcess->getTurnaroundTime() - currentProcess->getBurstTime());
                // alert process completion
                message << "P" << currentProcess->getPNo() << " finished at t=" << time;
                tui.alert(message.str());
                // clear message
                message.str("");
                // push current process to finished process list
                finished.push_back(*currentProcess);
                // set CPU to idle
                currentProcess = &process::CPUIDLE;
            }
        }
        // if the CPU is idle and there is something in the queue
        if (currentProcess == &process::CPUIDLE && !priorityQueue.empty()) {

            ///////////////////////////////
            // A NEW PROCESS BEGINS HERE //
            ///////////////////////////////

            // set current process to beginning of queue
            currentProcess = priorityQueue.front();
            // remove current process from wait queue
            priorityQueue.erase(priorityQueue.begin());
            // alert process beginning
            message << "P" << currentProcess->getPNo() << " started at t=" << time;
            tui.alert(message.str());
            // clear message
            message.str("");
        }
        // add current process to gantt chart
        tui.addToGanttChart(*currentProcess);
        // update tui
        tui.print();
        // time goes on
        currentProcess->incrementTimeElapsed();
    }
    if (tui.showResultOnly) {
        tui.showResultOnly = false;
        tui.print();
    }
    return finished;
}