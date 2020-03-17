cmake_minimum_required(VERSION 3.05)
set(CMAKE_CXX_STANDARD_REQUIRED 14)

project(pamsi-sorts VERSION 1.0)

add_executable(sorts
    ./src/main.cpp
    ./src/PrintTools.cpp
    ./src/Test/Tests.cpp
    ./src/Test/TestRunner.cpp)

target_include_directories(sorts PUBLIC src/)
