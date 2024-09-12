cmake_minimum_required(VERSION 3.26)
project(Lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab4 main.cpp
        Matrix.h
        Matrix.cpp
        Iterator.h
        Iterator.cpp
        ShortTest.h
        ShortTest.cpp
        ExtendedTest.h
        ExtendedTest.cpp)
