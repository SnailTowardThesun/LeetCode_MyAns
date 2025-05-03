cmake_minimum_required(VERSION 3.14)

Project(LeetCode_Ans_Cplusplus)

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
set(CMAKE_CXX_FLAGS "-g -std=c++14 -Wall")

set(TEST_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)
file(GLOB TEST_FILES "${TEST_SRC_DIR}/*.cpp")

enable_testing()

add_executable(
        tests
        ${TEST_FILES}
)
target_link_libraries(
        tests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)