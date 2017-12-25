/*
 * Bobby Martin
 * COMP3475 Operating Systems
 * Process Scheduling Algorithm Simulator
 *
 * main.cpp
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include "algorithms/FCFS.h"
#include "algorithms/SJF.h"
#include "algorithms/SRT.h"
#include "algorithms/priority.h"
#include "algorithms/RRVariable.h"
#include "algorithms/RRFixed.h"

using namespace std;

void printWelcome() {
    if (system("clear")) system("cls");
    cout << "##########################################################" << endl
         << "## Welcome to Bobby Martin's most excellently excellent ##" << endl
         << "##          Scheduling Algorithm Simulator!!!!          ##" << endl
         << "##########################################################" << endl
         << "              made with love by Bobby Martin" << endl << endl;
}

bool isInvalidInput(int input, int a, int b) {
    if (input < a || input > b) {
        cout << "You goofed! That's not an option." << endl << "Exiting...";
        return true;
    }
    return false;
}

int main() {
    // set up and seed random number generator
    default_random_engine generator(time(NULL));

    // processList is passed to the algorithm function
    vector<process> processList;
    // input is stored in these
    int algorithmChoice, inputChoice, numRandProcesses;
    // used in process creation
    int arrivalTime = -1, burstTime = -1, priorityvar = -1;
    // used as upper bounds in random arrival time and burst time generation
    int arrivalTimeUpperBound = -1, burstTimeUpperBound = -1;
    // used in round robin function calls
    int quantum;
    // used to store (y/n) inputs
    char inputChar;
    // used for TUI
    bool dontShowTimeline = true, showResultOnly = true;

    printWelcome();
    cout <<
         "Let's start with some algorithms:"<< endl << endl <<
         "[1] First come first serve" << endl <<
         "[2] Shortest job first" << endl <<
         "[3] Shortest remaining time" << endl <<
         "[4] Priority" << endl <<
         "[5] Round-Robin (fixed quantum)" << endl <<
         "[6] Round-Robin (variable quantum)" << endl << endl <<
         "Pick one to simulate [1-6]: ";
    // get algorithm choice
    cin >> algorithmChoice;
    // make sure input is valid
    if (isInvalidInput(algorithmChoice, 1, 6))
        return 1;
    cout << "Excellent choice!" << endl;

    // if chosen algorithm is a round robin variant
    if (algorithmChoice > 4) {
        cout << endl << "please enter round-robin quantum [1-99999]: ";
        // get quantum
        cin >> quantum;
        // make sure input is valid
        if (isInvalidInput(quantum, 1, 99999))
            return 1;
    }
    cout << endl << endl <<
         "Would you like to input your own processes or generate them randomly?" << endl << endl <<
         "[1] input my own" << endl <<
         "[2] generate them randomly" << endl << endl <<
         "Pick one [1-2]: ";
    // get choice
    cin >> inputChoice;

    // make sure input is valid, again
    if (isInvalidInput(inputChoice, 1, 2))
        return 1;

    // get processes from console input
    int i = 0; // keeps track of the process being input
    while (inputChoice == 1) {
        i++;
        cout << "== P" << i << " ==" << endl;
        // get arrival time
        cout << "please enter P" << i << "'s arrival time [0-99999]: ";
        cin >> arrivalTime;
        if (isInvalidInput(arrivalTime, 0, 99999))
            return 1;
        // get burst time
        cout << "please enter P" << i << "'s burst time [0-99999]: ";
        cin >> burstTime;
        if (isInvalidInput(burstTime, 0, 99999))
            return 1;
        // get priority
        cout << "please enter P" << i << "'s priority [1-99999]: ";
        cin >> priorityvar;
        if (isInvalidInput(priorityvar, 1, 99999))
            return 1;
        for (process p : processList)
            if (priorityvar == p.getPriority()) {
                cout << "priority conflicts with P" << p.getPNo() << endl << "Exiting...";
                return 1;
            }

        // add process to processList
        processList.emplace_back(arrivalTime, burstTime, priorityvar);
        cout << endl <<
             "enter another process? [y/n]: ";
        cin >> inputChar;
        // if inputChar == 'y', inputChoice = 1
        inputChoice = inputChar-'y'+1;
        // make sure we don't accidentally randomly generate a bunch of processes when we didn't mean to
        if (inputChoice == 2)
            inputChoice = 3;
    }

    // randomly generate processes
    if (inputChoice == 2) {
        cout << "Great!" << endl << endl << endl << "How many processes would you like to generate? [1-99999]: ";
        cin >> numRandProcesses;
        if (isInvalidInput(numRandProcesses, 1, 99999))
            return 1;

        cout << endl <<
             "please enter inclusive upper bound for arrival times" << endl <<
             "(processes will never arrive after this time) [0-99999]: ";
        // get arrival time upper bound
        cin >> arrivalTimeUpperBound;
        if (isInvalidInput(arrivalTimeUpperBound, 0, 99999))
            return 1;

        cout << endl <<
             "please enter inclusive upper bound for burst times" << endl <<
             "(processes will never take longer than this to execute) [1-99999]: ";
        cin >> burstTimeUpperBound;
        // get burst time upper bound
        if (isInvalidInput(burstTimeUpperBound, 1, 99999))
            return 1;

        int priorities[numRandProcesses];
        // priorities = {1, 2, ... n-1, n}
        // where n = number of processes
        for (int j = 0; j < numRandProcesses; j++)
            priorities[j] = j+1;
        // randomly reorder priorititee array
        shuffle(&priorities[0], &priorities[numRandProcesses], generator);
        /*
         * each element in the now shuffled priorities array is
         * assigned to a process' priority as it is randomly generated.
         * This is to simplify random priority generation while
         * also ensuring that each process has a unique priority.
         */

        // random progess generating happens here
        // set upper and lower bounds for arrival time and burst time
        uniform_int_distribution<int> arrivalDistribution(0, arrivalTimeUpperBound);
        uniform_int_distribution<int> burstDistribution(1, burstTimeUpperBound);
        for (int j = 0; j < numRandProcesses; j++) {
            // randomize arrival and burst times
            arrivalTime = arrivalDistribution(generator);
            burstTime = burstDistribution(generator);
            // see block comment above
            priorityvar = priorities[j];
            // add process to process list
            processList.emplace_back(arrivalTime, burstTime, priorityvar);
        }
    }

    // ask about simulation
    cout << endl <<
         "would you like to show the gantt chart being built? [y/n]: ";
    cin >> inputChar;
    if (inputChar == 'y')
        showResultOnly = false;

    // ask about timeline
    cout << endl <<
         "would you like to display the timeline?" << endl <<
         "(the timeline shows when processes arrive, start, finish, and get prempted) [y/n]: ";
    cin >> inputChar;
    if (inputChar == 'y')
        dontShowTimeline = false;

    int width = 25;
    cout << endl <<
         "enter width of gantt chart to display in units (one unit is 5 characters)" << endl <<
         "25 is a lovely choice if you're not sure [>0]: ";
    cin >> width;
    if (width < 1) {
        cout << "You goofed! That's not an option." << endl << "Exiting...";
        return 1;
    }

    int delay = 100;
    // if we're showing the gantt chart being generated
    if (!showResultOnly) {
        cout << endl <<
             "enter delay in ms between gantt chart updates: [1-10000]: ";
        // get delay between refreshes
        cin >> delay;
        if (isInvalidInput(delay, 1, 10000))
            return 1;
    }

    sillytui tui(width, delay);
    tui.showResultOnly = showResultOnly;
    tui.dontShowTimeline = dontShowTimeline;
    vector<process> finished;
    // do the deed
    switch (algorithmChoice) {
        case 1:
            finished = FCFS(processList, tui);
            break;
        case 2:
            finished = SJF(processList, tui);
            break;
        case 3:
            finished = SRT(processList, tui);
            break;
        case 4:
            finished = priority(processList, tui);
            break;
        case 5:
            finished = RRFixed(processList, quantum, tui);
            break;
        case 6:
            finished = RRVariable(processList, quantum, tui);
            break;
        default:
            cout << "how did you do that?" << endl << "Exiting...";
            return 1;
    }
    // sort results by process number
    sort(finished.begin(), finished.end(), sortByPNo);
    // print results table
    tui.printTable(finished);

    return 0;
}
