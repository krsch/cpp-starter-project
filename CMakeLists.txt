cmake_minimum_required(VERSION 3.10.0)

project(Homework CXX)
set(CMAKE_CXX_STANDARD 17)
include(cmake/StandardProjectSettings.cmake)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_17)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(default)

enable_testing()
add_subdirectory(external/doctest)
include(external/doctest/doctest.cmake)
add_subdirectory(src)
