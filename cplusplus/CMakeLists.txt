cmake_minimum_required(VERSION 3.28)

project(LeetCode_Ans_Cplusplus)

include (FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# compile params
set(CMAKE_CXX_FLAGS "-g -std=c++20 -Wall")

# 每日一题：CONFIGURE_DEPENDS 让新增 .cpp 后仅执行 make 即可自动重新收集并编译
set(TEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/questions)
file(GLOB TEST_FILES CONFIGURE_DEPENDS "${TEST_SRC_DIR}/*.cpp")

# Top 150 题目文件
set(TOP150_DIR ${CMAKE_CURRENT_SOURCE_DIR}/top150)
file(GLOB_RECURSE TOP150_FILES CONFIGURE_DEPENDS "${TOP150_DIR}/**.cpp")
list(APPEND TEST_FILES ${TOP150_FILES})

enable_testing()

add_executable(
        tests
        ${TEST_FILES}
        questions/2089.cpp
)

target_link_libraries(
        tests
        GTest::gtest_main
)

# 供各题解 #include "leetcode_common.h"（通用 ListNode/TreeNode 定义）
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(tests)
