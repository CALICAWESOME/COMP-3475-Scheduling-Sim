# HOW TO COMPILE (using g++):
- compile main.cpp and all .cpp files in the algorithms, process, and tui directories using the `-std =c++11` flag

example (with wildcards):<br>
`g++ -std=c++11 main.cpp algorithms/*.cpp process/process.cpp tui/tui.cpp`

*note: sillytui.cpp uses windows.h for delay, this will only compile on Windows*

# HOW TO RUN:
- run "PA_Scheduling_Sim.exe"