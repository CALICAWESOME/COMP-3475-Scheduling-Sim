/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * RRFixed.h
 */
#ifndef PA_SCHEDULING_SIM_RRFIXED_H
#define PA_SCHEDULING_SIM_RRFIXED_H

#include <vector>
#include "../process/process.h"
#include "../tui/sillytui.h"

using namespace std;

vector<process> RRFixed(vector<process>, int, sillytui);

#endif //PA_SCHEDULING_SIM_RRFIXED_H
