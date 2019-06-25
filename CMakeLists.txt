cmake_minimum_required(VERSION 3.11)

project(tl-function_ref VERSION 1.0.0 LANGUAGES CXX)

option(FUNCTION_REF_ENABLE_TESTS "Enable tests." ON)

include(FetchContent)
FetchContent_Declare(
  tl_cmake
  GIT_REPOSITORY https://github.com/TartanLlama/tl-cmake.git
)
FetchContent_GetProperties(tl_cmake)
if(NOT tl_cmake_POPULATED)
  FetchContent_Populate(tl_cmake)
  set(CMAKE_MODULE_PATH ${tl_cmake_SOURCE_DIR} ${CMAKE_MODULE_PATH})
endif()
include(add-tl)

tl_add_library(function-ref SOURCES 
               include/tl/function_ref.hpp)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

if(FUNCTION_REF_ENABLE_TESTS)
  # Make test executable
  set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/call.cpp  
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/issues.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/assignment.cpp)
  
  add_executable(tests ${TEST_SOURCES})
  
  target_link_libraries(tests Catch function-ref)

  set_property(TARGET tests PROPERTY CXX_STANDARD 14)
endif()