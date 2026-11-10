cmake_minimum_required(VERSION 3.14)
project(DataStructure LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Algorithms STATIC
    lib_easy_example/easy_example.cpp
    lib_easy_example/easy_example.h
)
target_include_directories(Algorithms PUBLIC lib_easy_example)

add_executable(DS_APP main/main.cpp)
target_link_libraries(DS_APP PRIVATE Algorithms)
set_target_properties(DS_APP PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/main"
)

option(BTEST "Build tests" ON)
if(BTEST)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    add_subdirectory(third_party/gtest EXCLUDE_FROM_ALL)
    enable_testing()

    add_executable(DS_TESTS tests/test_easy_example.cpp)
    target_link_libraries(DS_TESTS PRIVATE Algorithms gtest_main)
    set_target_properties(DS_TESTS PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests"
    )
    add_test(NAME DS_TESTS COMMAND DS_TESTS)
endif()
