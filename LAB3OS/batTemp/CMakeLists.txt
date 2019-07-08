cmake_minimum_required(VERSION 3.12)
project(batTemp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(batTemp main.cpp BatFunctions.cpp BatFunctions.h DeadLock.cpp DeadLock.h Monitor.cpp Monitor.h)