/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * SJF.cpp
 */
#include <algorithm>
#include <iostream>
#include <sstream>
#include "SJF.h"

////////////////////////
// SHORTEST JOB FIRST //
////////////////////////
vector<process> SJF(vector<process> inputList, sillytui tui) {
    sort(inputList.rbegin(), inputList.rend(), sortByArrivalTime);

    stringstream message;

    process* currentProcess = &process::CPUIDLE;
    vector<process*> SJFQueue;
    vector<process> finished;

    // ye control loop!
    for (int time = 0, numProc = inputList.size(); finished.size() < numProc; time++) {
        // check for arriving processes (every time)
        while (inputList.back().getArrivalTime() == time) {

            ///////////////////////////
            // PROCESSES ARRIVE HERE //
            ///////////////////////////

            // imHere = arriving process
            process* imHere = &inputList.back();
            // remove arriving process from input list
            inputList.pop_back();
            // push arriving process to wait queue
            SJFQueue.push_back(imHere);
            // reorder wait queue by burst time
            sort(SJFQueue.begin(), SJFQueue.end(), sortPointersByBurstTime);
            // alert process arrival
            message << "P" << imHere->getPNo() << " arrived at t=" << time;
            tui.alert(message.str());
            // clear message
            message.str("");
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
        if (currentProcess == &process::CPUIDLE && !SJFQueue.empty()) {

            ///////////////////////////////
            // A NEW PROCESS BEGINS HERE //
            ///////////////////////////////

            // set current process to beginning of queue
            currentProcess = SJFQueue.front();
            // remove current process from wait queue
            SJFQueue.erase(SJFQueue.begin());
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