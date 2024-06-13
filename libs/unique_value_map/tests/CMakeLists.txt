cmake_minimum_required(VERSION 3.10)
 
project(tests C CXX ASM)

set(TARGET runTests)

add_executable(${TARGET} test.cpp)

target_include_directories(${TARGET} PUBLIC
    ../include
)

find_package(GTest REQUIRED)
target_include_directories(${TARGET} PUBLIC ${GTEST_INCLUDE_DIRS})

target_link_libraries(${TARGET} ${GTEST_LIBRARIES} pthread)