# Process Scheduling Simulator
Thie is a project written for COMP 3475 (Operating Systems) to simulate 6 different types of CPU process scheduling algorithms. The algorithms are as follows:
- FCFS (first come first served)
- SJF (shortest job first)
- SRT (shortest remaining time)
- Fixed priority pre-emptive
- Round-robin with a fixed quantum
- Round-robin with a variable quantum

Instructions for running each one are included in the program.

## Build me!
```bash
$ git clone https://github.com/CALICAWESOME/COMP-3475-Scheduling-Sim
$ cd COMP-3475-Scheduling-Sim
$ mkdir build
$ cd build
$ cmake ..
$ make
$ ./sim 
```

## Future endeavors
I'd like to port the UI for this to ncurses. Right now it's just a big bunch of print statements with a `system("clear")` in between each refresh which is pretty freaking nasty.
