cmake_minimum_required(VERSION 3.12)
project(tl-function_ref
  HOMEPAGE_URL "https://github.com/TartanLlama/function_ref"
  DESCRIPTION "A lightweight, non-owning reference to a callable"
  VERSION 1.0.0
  LANGUAGES CXX)

include(CMakePackageConfigHelpers)
include(CMakeDependentOption)
include(GNUInstallDirs)
include(FetchContent)
include(CTest)

if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

cmake_dependent_option(FUNCTION_REF_BUILD_TESTS
  "Enable tl::function_ref tests" ON
  "BUILD_TESTING;CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR" OFF)

add_library(function-ref INTERFACE)
target_include_directories(function-ref
  INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
if (NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  add_library(tl::function-ref ALIAS function-ref)
endif()

configure_package_config_file(
  "${PROJECT_SOURCE_DIR}/cmake/tl-function-ref-config.cmake.in"
  "${PROJECT_BINARY_DIR}/tl-function-ref-config.cmake.in"
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/tl-function-ref
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  NO_SET_AND_CHECK_MACRO)

write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/tl-function-ref-config-version.cmake"
  COMPATIBILITY SameMajorVersion
  ARCH_INDEPENDENT)

install(TARGETS function-ref EXPORT tl-function-ref-targets)
install(EXPORT tl-function-ref-targets
  DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/tl-function-ref
  NAMESPACE tl::
  FILE tl-function-ref-targets.cmake)

install(FILES
  "${PROJECT_BINARY_DIR}/tl-function-ref-config-version.cmake"
  "${PROJECT_BINARY_DIR}/tl-function-ref-config.cmake.in"
  DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/tl-function-ref)

install(DIRECTORY "include/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (FUNCTION_REF_BUILD_TESTS)
  set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
  set(CATCH_INSTALL_HELPERS OFF)
  set(CATCH_BUILD_TESTING OFF)
  set(CATCH_INSTALL_DOCS OFF)
  FetchContent_Declare(catch2 URL
    https://github.com/catchorg/Catch2/archive/v2.9.2.zip) 
  if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
  endif()
  file(GENERATE OUTPUT catch.main.cpp
    CONTENT [[
      #define CATCH_CONFIG_MAIN
      #include <catch2/catch.hpp>
  ]])
  set_property(SOURCE "${PROJECT_BINARY_DIR}/catch.main.cpp" PROPERTY GENERATED ON)
  add_library(tl-function-ref-catch-main OBJECT)
  target_sources(tl-function-ref-catch-main
    PRIVATE "${PROJECT_BINARY_DIR}/catch.main.cpp")
  target_compile_options(tl-function-ref-catch-main
    PUBLIC
      $<$<AND:$<CXX_COMPILER_ID:Clang>,$<BOOL:"$ENV{TRAVIS}">>:-stdlib=libc++>
      $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra>)
  target_link_options(tl-function-ref-catch-main
    PUBLIC
      $<$<AND:$<CXX_COMPILER_ID:Clang>,$<BOOL:"$ENV{TRAVIS}">>:-stdlib=libc++>)
  target_link_libraries(tl-function-ref-catch-main
    PUBLIC
      Catch2::Catch2
      function-ref)
    file(GLOB test-sources CONFIGURE_DEPENDS tests/*.cpp)
    foreach (source IN LISTS test-sources)
      get_filename_component(name "${source}" NAME_WE)
      set(test "function-ref-test-${name}")
      add_executable(${test}
        "${source}"
        $<TARGET_OBJECTS:tl-function-ref-catch-main>)
      target_link_libraries(${test} PRIVATE tl-function-ref-catch-main)
      add_test(NAME function-ref::test::${name} COMMAND ${test})
    endforeach()
endif()
