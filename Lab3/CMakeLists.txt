cmake_minimum_required(VERSION 3.26)
project(Lab3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab3 main.cpp
        IteratedList.h
        IteratedList.cpp
        ShortTest.h
        ShortTest.cpp
        ExtendedTest.h
        ExtendedTest.cpp
        ListIterator.h
        ListIterator.cpp)
