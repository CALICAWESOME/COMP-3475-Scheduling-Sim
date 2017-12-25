/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * sillytui.cpp
 */
#include <iostream>
#include <iomanip>
#include <thread>
#include "sillytui.h"

// TODO: NCURSES MY GUY

void sleep(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

sillytui::sillytui(int width, int delay) {
    this->width = width;
    this->delay = delay;
    showResultOnly = false;
}

void sillytui::addToGanttChart(process p) {
    ganttChart.push_back(p);
}

void sillytui::alert(string message) {
    messages.push_back(message);
}

void sillytui::print() {
    // do nothing if showResultsOnly is set
    if (this->showResultOnly)
        return;
    /*
     * editor's note:
     * I understand that using system() is terrible practice.
     * It also makes printing the gantt chart as it is generated
     * look very goofy (hence the name, sillytui). My original
     * plan was to write this entire UI using ncurses but Windows
     * doesn't support it and I ran out of time to think of a
     * more sensible alternative.
     *
     * See the TODO at the top of this file
     */
    if (system("clear")) system("cls");

    // these represent the last and current process being printed
    process lastProcessTop = process::CPUIDLE;
    process currentProcessTop = process::CPUIDLE;
    process lastProcess = process::CPUIDLE;
    process currentProcess = process::CPUIDLE;

    // show timeline
    if (!dontShowTimeline) {
        cout << "== TIMELINE ==" << endl;
        for (string& message : messages) {
            cout << message << endl;
        }
        cout << endl;
    }

    cout << "== GANTT CHART ==" << endl << endl << "(#### = idle time)" << endl;
    /*
     * Each row of the gantt chart is sillytui::width processes wide.
     * Each process is 5 characters long.
     */
    // for each row in gantt chart
    for (int i = 0; i <= ganttChart.size()/width; i++) {

        // do the top bar of each process first
        for (int j = 0; j < width && (i*width + j) < ganttChart.size(); j++) {
            // keep track of the proces sbeing printed
            currentProcessTop = ganttChart.at(i*width + j);

            if (currentProcessTop.getPNo() == 0)
                cout << "     ";
            else if (currentProcessTop.getPNo() != lastProcessTop.getPNo())
                cout << " ____";
            else
                cout << "_____";

            lastProcessTop = currentProcessTop;
        }
        // starting the top
        cout << endl;

        // show sillytui::width processes
        // also don't try to print more processes than exist in the gantt chart
        // (hence the  in the condition)
        for (int j = 0; j < width && (i*width + j) < ganttChart.size(); j++) {

            // keep track of the proces sbeing printed
            currentProcess = ganttChart.at(i*width + j);

            // format spacing and display pno
            if (currentProcess.getPNo() == 0)
                if (lastProcess.getPNo() != 0) cout << "|####";
                else cout << "#####";
            else if (currentProcess.getPNo() != lastProcess.getPNo())
                cout << left << "|P" << setw(3) << setfill('_') << currentProcess.getPNo();
            else {
                cout << "_____";
            }

            // store currentProcess in lastProcess, we will refer to it in the next iteration
            lastProcess = currentProcess;
        }
        if (lastProcess.getPNo() != 0)
            cout << '|';
        else
            cout << '#';
        cout << endl;

        // show every 5 time starting with 0
        for (int j = 0; j < width && (i*width + j) < ganttChart.size(); j++) {
            // store time in a variable so I don't have to keep typing it
            int time = i*width + j;
            // format spacing & print time below gantt chart
            cout << left << setfill(' ') << setw(5) << time;
            // fix end of line
            if (j == width-1)
                cout << time+1;
        }
        cout << endl << endl;
    }
    // sleepytime
    sleep(delay);
}

void sillytui::printTable(vector<process> finished) {
    double avgwait = 0, avgtat = 0;

    // show table
    cout << "== THE RESULTS ==" << endl;
    cout << "_/_process_/_arrival_time_/_burst_time_/_priority_/_wait_time_/_turnaround_time_/_" << endl;
    for (process p : finished) {
        cout << " | P" << setw(6) << left << p.getPNo();
        cout << " | " << setw(12) << right << p.getArrivalTime();
        cout << " | " << setw(10) << right << p.getBurstTime();
        cout << " | " << setw(8) << right << p.getPriority();
        cout << " | " << setw(9) << right << p.getWaitTime();
        cout << " | " << setw(15) << right << p.getTurnaroundTime();
        cout << " | " << endl;
        avgwait += p.getWaitTime();
        avgtat += p.getTurnaroundTime();
    }
    // calculate average wait and turnaround time
    avgwait /= finished.size();
    avgtat /= finished.size();
    cout << endl << "AVG. WAIT TIME: " << avgwait << endl << "AVG. TURNAROUND TIME: " << avgtat << endl;
}
