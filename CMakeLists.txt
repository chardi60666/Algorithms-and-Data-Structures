cmake_minimum_required(VERSION 3.14)

project(Algorithms-and-Data-Structures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/function.cmake)

# Libraries must be registered before applications and tests.
add_subdirectory(lib_easy_example)
add_subdirectory(lib_vector)
add_subdirectory(main)

option(BTEST "Build Google Test tests" ON)
if(BTEST)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  if(NOT EXISTS "${CMAKE_SOURCE_DIR}/third_party/gtest/CMakeLists.txt")
    message(FATAL_ERROR
      "Google Test is missing. Run: "
      "git submodule update --init --recursive")
  endif()
  add_subdirectory(third_party/gtest EXCLUDE_FROM_ALL)
  enable_testing()
  add_subdirectory(tests)
endif()
