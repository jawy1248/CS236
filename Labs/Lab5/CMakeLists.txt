cmake_minimum_required(VERSION 3.27)
project(Lab5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab5
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
        Tuple.h
        Node.h
        Graph.h)
