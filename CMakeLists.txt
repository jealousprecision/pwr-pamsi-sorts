cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

project(pamsi-sorts VERSION 1.0)

find_package(Threads)

add_executable(sorts
    ./src/main.cpp
    ./src/PrintTools.cpp
    ./src/Test/SimpleTests.cpp
    ./src/Test/MainTest.cpp
    ./src/Test/NewTestRunner.cpp
    ./src/Test/ThreadedTestRunner.cpp
    ./src/Test/BasicTestFactory.cpp
    ./src/Test/MainTestFactory.cpp)

target_include_directories(sorts PUBLIC src/)
target_link_libraries(sorts ${CMAKE_THREAD_LIBS_INIT})
