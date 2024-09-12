cmake_minimum_required(VERSION 3.26)
project(Lab2)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab2 main.cpp
        MultiMap.h
        MultiMap.cpp
        MultiMapIterator.h
        MultiMapIterator.cpp
        ShortTest.h
        ShortTest.cpp
        ExtendedTest.h
        ExtendedTest.cpp)
