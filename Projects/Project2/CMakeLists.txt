cmake_minimum_required(VERSION 3.27)
project(Project2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project2
        main.cpp
        Parser.h
        Scanner.h
        Token.h
        Parameter.h)
