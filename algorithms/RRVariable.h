/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * RRVariable.h
 */
#ifndef PA_SCHEDULING_SIM_RRVARIABLE_H
#define PA_SCHEDULING_SIM_RRVARIABLE_H

#include <vector>
#include "../process/process.h"
#include "../tui/sillytui.h"

using namespace std;

vector<process> RRVariable(vector<process>, int, sillytui);

#endif //PA_SCHEDULING_SIM_RRVARIABLE_H
