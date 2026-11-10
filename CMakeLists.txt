cmake_minimum_required(VERSION 3.14)

project(Algorithms-and-Data-Structures LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(EasyExample STATIC
  lib_easy_example/easy_example.cpp
  lib_easy_example/easy_example.h
)
target_include_directories(EasyExample PUBLIC lib_easy_example)

add_library(Vector STATIC
  libs/vector/src/TVector.cpp
  libs/vector/include/TVector.h
  libs/vector/include/TMemData.h
)
target_include_directories(Vector PUBLIC libs/vector/include)

add_executable(Application main/main.cpp)
target_link_libraries(Application PRIVATE EasyExample Vector)
set_target_properties(Application PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/main"
)

option(BTEST "Build Google Test tests" ON)
if(BTEST)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/gtest/CMakeLists.txt")
    message(FATAL_ERROR
      "Google Test is missing. Run: "
      "git submodule update --init --recursive")
  endif()
  set(BUILD_GMOCK OFF)
  add_subdirectory(third_party/gtest EXCLUDE_FROM_ALL)
  enable_testing()

  add_executable(AllTests tests/test_all.cpp)
  target_link_libraries(AllTests PRIVATE EasyExample Vector gtest_main)
  set_target_properties(AllTests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/tests"
  )
  add_test(NAME AllTests COMMAND AllTests)
endif()
