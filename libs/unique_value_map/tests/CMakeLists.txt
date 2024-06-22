cmake_minimum_required(VERSION 3.10)

message(STATUS "(MOJE) C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "(MOJE) C++ Compiler: ${CMAKE_CXX_COMPILER}")

project(tests C CXX ASM)

set(TARGET runTests)

add_executable(${TARGET}
    test.cpp
    ../src/UniqueValueMap.cpp
)

target_include_directories(${TARGET} PUBLIC
    ../include
    ${GTEST_INCLUDE_DIRS}
)

find_package(GTest REQUIRED)

target_link_libraries(${TARGET} ${GTEST_LIBRARIES} pthread)