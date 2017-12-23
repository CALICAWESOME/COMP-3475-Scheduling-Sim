/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * FCFS.h
 */
#ifndef PA_SCHEDULING_SIM_FCFS_H
#define PA_SCHEDULING_SIM_FCFS_H

#include <vector>
#include "../process/process.h"
#include "../tui/sillytui.h"

using namespace std;

vector<process> FCFS(vector<process>, sillytui);

#endif //PA_SCHEDULING_SIM_FCFS_H