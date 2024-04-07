cmake_minimum_required(VERSION 3.27)
project(Project5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project5
        Database.h
        DatalogProgram.h
        Graph.h
        Interpreter.h
        main.cpp
        Node.h
        Parameter.h
        Parser.h
        Predicate.h
        Relation.h
        Rule.h
        Scanner.h
        Scheme.h
        Token.h
        Tuple.h)
