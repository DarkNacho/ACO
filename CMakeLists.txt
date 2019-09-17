cmake_minimum_required(VERSION 3.14)
project(ACO)

set(CMAKE_CXX_STANDARD 14)

add_executable(ACO main.cpp utils.h Graph.cpp Graph.h Ant.cpp Ant.h)