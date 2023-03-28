cmake_minimum_required(VERSION 3.22)
project(Tep6)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tep6 main.cpp CIndividual.cpp CIndividual.h CGeneticAlgorithm.cpp CGeneticAlgorithm.h CKnapsackProblem.cpp CKnapsackProblem.h)
