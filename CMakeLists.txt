cmake_minimum_required(VERSION 3.14)
project(DataStructure LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Algorithms STATIC
    lib_easy_example/easy_example.cpp
    lib_easy_example/easy_example.h
    lib_structures/brackets.cpp
    lib_structures/brackets.h
    lib_structures/queue.h
    lib_structures/stack.h
)
target_include_directories(Algorithms PUBLIC lib_easy_example ${CMAKE_CURRENT_SOURCE_DIR})

add_library(List STATIC lib_list/list.cpp lib_list/list.h)
target_include_directories(List PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(DS_APP main/main.cpp)
target_link_libraries(DS_APP PRIVATE Algorithms List)
set_target_properties(DS_APP PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/main"
)

option(BTEST "Build tests" ON)
if(BTEST)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF)
    set(INSTALL_GTEST OFF)
    add_subdirectory(third_party/gtest EXCLUDE_FROM_ALL)
    enable_testing()

    add_executable(DS_TESTS tests/test_easy_example.cpp tests/test_structures.cpp tests/test_list.cpp)
    target_link_libraries(DS_TESTS PRIVATE Algorithms List gtest_main)
    set_target_properties(DS_TESTS PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests"
    )
    add_test(NAME DS_TESTS COMMAND DS_TESTS)
endif()
