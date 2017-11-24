cmake_minimum_required(VERSION 3.0)

project(function_ref)

# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/test)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test executable
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/constructors.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/call.cpp  
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/assignment.cpp)

add_executable(tests ${TEST_SOURCES})

add_library(function_ref INTERFACE)
target_sources(function_ref INTERFACE ${CMAKE_SOURCE_DIR}/function_ref.hpp)
target_include_directories(function_ref INTERFACE ${CMAKE_SOURCE_DIR})

target_link_libraries(tests Catch function_ref)
set_property(TARGET tests PROPERTY CXX_STANDARD 14)


find_package(standardese) # find standardese after installation

# generates a custom target that will run standardese to generate the documentation
if (standardese_FOUND)
standardese_generate(function_ref
                     INCLUDE_DIRECTORY .
                     CONFIG ${CMAKE_SOURCE_DIR}/standardese.config
                     INPUT function_ref.hpp)
endif ()
