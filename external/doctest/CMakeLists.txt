cmake_minimum_required(VERSION 3.5)
project(doctest LANGUAGES CXX VERSION 2.3.8)

add_library(doctest STATIC doctest.cpp)
target_compile_features(doctest PUBLIC cxx_std_11)
# depend on some obvious c++11 features so the dependency is transitively added dependents
target_include_directories(doctest PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
include(doctest.cmake)

add_library(doctest::doctest ALIAS doctest)
add_library(Catch2::Catch2 ALIAS doctest)
