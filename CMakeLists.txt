cmake_minimum_required(VERSION 3.0)
project (Scheduling-Sim)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(algorithms ALGORITHMS)
aux_source_directory(process PROCESS)
aux_source_directory(tui TUI)
set(SOURCE_FILES main.cpp ${ALGORITHMS} ${PROCESS} ${TUI})

add_executable(sim ${SOURCE_FILES})
