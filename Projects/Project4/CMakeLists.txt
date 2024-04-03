cmake_minimum_required(VERSION 3.27)
project(Project4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project4
        Database.h
        DatalogProgram.h
        Interpreter.h
        main.cpp
        Parameter.h
        Parser.h
        Predicate.h
        Relation.h
        Rule.h
        Scanner.h
        Scheme.h
        Token.h
        Tuple.h)
