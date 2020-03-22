cmake_minimum_required(VERSION 3.05)
set(CMAKE_CXX_STANDARD_REQUIRED 14)

project(pamsi-sorts VERSION 1.0)

add_executable(sorts
    ./src/main.cpp
    ./src/PrintTools.cpp
    ./src/Test/SimpleTests.cpp
    ./src/Test/MainTest.cpp
    ./src/Test/TestRunner.cpp
    ./src/Test/BasicTestFactory.cpp
    ./src/Test/MainTestFactory.cpp)

set(CMAKE_CXX_FLAGS "-Wall")

target_include_directories(sorts PUBLIC src/)
