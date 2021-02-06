cmake_minimum_required(VERSION 3.10.0)

project(Homework CXX)
set(CMAKE_CXX_STANDARD 17) # CMAKE_CXX_STANDARD = 17
include(cmake/StandardProjectSettings.cmake)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(default INTERFACE)
target_compile_features(default INTERFACE cxx_std_17)

include(cmake/CompilerWarnings.cmake)
set_project_warnings(default)
include(cmake/conan.cmake)
get_property(languages GLOBAL PROPERTY ENABLED_LANGUAGES)
set(ENV_FOR_C CC)
set(ENV_FOR_CXX CXX)
set(ENV_FOR_Fortran FC)
foreach(language ${languages})
  if(ENV_FOR_${language})
    list(APPEND ENV "${ENV_FOR_${language}}=${CMAKE_${language}_COMPILER}")
  else()
    list(APPEND ENV "${language}=${CMAKE_${language}_COMPILER}")
  endif()
endforeach()
conan_cmake_run(
  CONANFILE conanfile.txt
  BASIC_SETUP CMAKE_TARGETS BUILD missing
  ENV CONAN_CMAKE_PROGRAM="${CMAKE_COMMAND}" ${ENV}
  )

enable_testing()
add_subdirectory(external/doctest)
include(external/doctest/doctest.cmake)
add_subdirectory(src)
