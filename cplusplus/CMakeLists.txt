cmake_minimum_required(VERSION 3)

Project(LeetCode_Ans_Cplusplus)

# compile params
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall")

set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set (SRC_FILE_LISTS ${SRC_DIR}/main.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/objs/)
add_executable(LeetCode_Ans ${SRC_FILE_LISTS})