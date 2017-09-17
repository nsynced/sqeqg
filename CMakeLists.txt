cmake_minimum_required(VERSION 3.3)
project(sqeqg)

set(SOURCES src/sqeqg.cpp src/SQEQGenerator.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
include_directories(external/cxxopts/include)

add_executable(sqeqg ${SOURCES})