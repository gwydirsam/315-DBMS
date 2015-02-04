# version 2.8.12 is on unix.cse.tamu.edu
cmake_minimum_required(VERSION 2.8.12)

# Set Project_Name and Language
set(PROJECT_NAME "dbapp")
project(${PROJECT_NAME} CXX)

# Unit testing with Google Test
# to run tests use 'cmake -Dtest=ON'
option(test "Build ${PROJECT_NAME}'s tests" OFF)

# set some locations
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDES_DIR "${CMAKE_SOURCE_DIR}/include")

# add directory for project source files
add_subdirectory(${SOURCE_DIR})

# set compilation variables
set(CXXFLAGS "-Wall -Wextra -std=c++14")
set(CXXFLAGS_RELEASE "${CXXFLAGS} -O3 -DNDEBUG")
set(CXXFLAGS_DEBUG "${CXXFLAGS} -g -O0 -DDEBUG")