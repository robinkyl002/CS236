cmake_minimum_required(VERSION 3.26)
project(project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project1
        FiniteStateMachines.h
        main.cpp
        Scanner.h
        Token.h
        project1-passoff/
        )
