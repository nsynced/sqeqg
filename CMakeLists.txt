cmake_minimum_required(VERSION 2.6)
project(sqeqg)

set(SOURCES src/sqeqg.cpp src/SQEQGenerator.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_executable(sqeqg ${SOURCES})
