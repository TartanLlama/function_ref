cmake_minimum_required(VERSION 3.11)

project(tl-function_ref VERSION 1.0.0 LANGUAGES CXX)

option(FUNCTION_REF_ENABLE_TESTS "Enable tests." ON)

include(FetchContent)
FetchContent_Declare(
  tl_cmake
  GIT_REPOSITORY https://github.com/burnpanck/tl-cmake.git
  GIT_TAG b6fe9104d205cf04c4aac3824c2d310959b66120
)
FetchContent_GetProperties(tl_cmake)
if(NOT tl_cmake_POPULATED)
  FetchContent_Populate(tl_cmake)
  set(CMAKE_MODULE_PATH ${tl_cmake_SOURCE_DIR} ${CMAKE_MODULE_PATH})
endif()
include(add-tl)

tl_add_library(function-ref ARCH_INDEPENDENT SOURCES 
               include/tl/function_ref.hpp)

# make sure we see the C++ version, even in MSVC:
# https://stackoverflow.com/questions/57102212/cannot-set-cplusplus-to-c17-standard-with-visual-studio-and-cmake
if ((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))
  target_compile_options(function-ref INTERFACE "/Zc:__cplusplus")
endif()

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

  message(STATUS "CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")
  if(NOT CMAKE_CXX_STANDARD)
    set_property(TARGET tests PROPERTY CXX_STANDARD 14)
  endif()
endif()
