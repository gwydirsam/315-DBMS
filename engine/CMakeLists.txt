cmake_minimum_required(VERSION 2.8.12)
project (dbengine)

# set some locations
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")

# set compilation variables
set(CXXFLAGS "-Wall -Wextra -std=c++14")
set(CXXFLAGS_RELEASE "${CXXFLAGS} -O3 -DNDEBUG")
set(CXXFLAGS_DEBUG "${CXXFLAGS} -g -O0 -DDEBUG")

# add directory for project source files
add_subdirectory(${SOURCE_DIR})

# Unit testing with Google Test
option(unit_tests "Build dbengine's unit tests" OFF)