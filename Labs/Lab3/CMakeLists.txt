cmake_minimum_required(VERSION 3.27)
project(Lab3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3
        DatalogProgram.h
        main.cpp
        Parameter.h
        Parser.h
        Predicate.h
        Rule.h
        Scanner.h
        Scheme.h
        Token.h
        Tuple.h
        Relation.h)
