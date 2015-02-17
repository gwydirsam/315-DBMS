# Set Project_Name and Language
set(PROJECT_NAME "dbengine")
project(${PROJECT_NAME} CXX)

# version 2.8.12 is on unix.cse.tamu.edu
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -Wall -Wextra")

# Unit testing with Google Test
# to run tests use 'cmake -Dtest=ON'
option(test "Build ${PROJECT_NAME}'s tests" OFF)

# set some locations
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDES_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

# include directories
include_directories(lib)

# set names
set(RELEASE_BINARY "main")
set(RELEASE_BINARY_OUTNAME "${PROJECT_NAME}")
set(UNITTEST_BINARY "${PROJECT_NAME}test")
set(ENGINE_LIBRARY "${PROJECT_NAME}")

# add directory for project source files and libraries
add_subdirectory(${SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
add_subdirectory(${LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/lib)
