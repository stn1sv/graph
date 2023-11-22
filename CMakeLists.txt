cmake_minimum_required(VERSION 3.25)
project(graph)

set(CMAKE_CXX_STANDARD 17)

add_executable(graph main.cpp Graph.h List.cpp PQueue.cpp Graph.cpp func.cpp)
