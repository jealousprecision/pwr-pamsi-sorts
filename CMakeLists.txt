cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

project(pamsi-sorts VERSION 1.0)

add_executable(sorts ./src/main.cpp ./src/Sorts.cpp)
target_include_directories(sorts PUBLIC src/)
