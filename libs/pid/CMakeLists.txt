cmake_minimum_required(VERSION 3.10)

project(pid)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SRC_FILES
    src/PID.cpp
)

add_library(pid STATIC ${SRC_FILES})

target_include_directories(pid include)