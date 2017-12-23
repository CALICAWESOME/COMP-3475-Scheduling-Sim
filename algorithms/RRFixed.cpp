/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * RRFixed.cpp
 */
#include <algorithm>
#include <iostream>
#include <sstream>
#include "RRFixed.h"

///////////////////////////////
// FIXED-QUANTUM ROUND ROBIN //
///////////////////////////////
vector<process> RRFixed(vector<process> inputList, int quantum, sillytui tui) {
    sort(inputList.rbegin(), inputList.rend(), sortByArrivalTime);

    stringstream message;

    process* currentProcess = &process::CPUIDLE;
    vector<process*> waitQueue;
    vector<process> finished;

    // ye control loop!
    for (int time = 0, numProc = inputList.size(); finished.size() < numProc; time++) {
        // check for arriving processes (every time)
        // bad guy shows up at t=3
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
            // push arriving process to wait queue
            waitQueue.push_back(imHere);
            // remove arriving process from input list
            inputList.pop_back();
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
        // if time is a multiple of quantum
        if (!(time % quantum)) {

            ////////////////////////////////
            // END OF QUNTUM HAPPENS HERE //
            ////////////////////////////////

            // if CPU is not idle
            if (currentProcess != &process::CPUIDLE) {
                // push current process to end of wait queue
                waitQueue.push_back(currentProcess);
                // alert end of quantum
                message << "P" << currentProcess->getPNo() << "'s quantum ended at t=" << time;
                tui.alert(message.str());
                // clear message
                message.str("");
            }
            // set CPU to idle
            currentProcess = &process::CPUIDLE;
            // if the CPU is idle and there is something in the queue
            if (!waitQueue.empty()) {

                ///////////////////////////////
                // A NEW PROCESS BEGINS HERE //
                ///////////////////////////////

                // set current process to beginning of queue
                currentProcess = waitQueue.front();
                // remove current process from wait queue
                waitQueue.erase(waitQueue.begin());
                // alert process beginning
                message << "P" << currentProcess->getPNo() << " started at t=" << time;
                tui.alert(message.str());
                // clear message
                message.str("");
            }
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