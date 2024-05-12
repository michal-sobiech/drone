cmake_minimum_required(VERSION 3.10)

project(MPU6050)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    MPU6050.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

