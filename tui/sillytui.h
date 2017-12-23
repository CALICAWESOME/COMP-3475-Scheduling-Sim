/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * sillytui.h
 */
#ifndef PA_SCHEDULING_SIM_SILLYTUI_H
#define PA_SCHEDULING_SIM_SILLYTUI_H

#include <vector>
#include "../process/process.h"

void sleep(int);

class sillytui {
    vector<process> ganttChart;
    vector<string> messages;
    int width;  // number of gantt chart blocks to display before a newline
    int delay;  // delay in ms between gantt chart prints


public:
    bool showResultOnly;
    bool dontShowTimeline;

    sillytui(int, int);

    void addToGanttChart(process);
    void alert(string);
    void print();
    void printTable(vector<process>);

};

#endif //PA_SCHEDULING_SIM_SILLYTUI_H
