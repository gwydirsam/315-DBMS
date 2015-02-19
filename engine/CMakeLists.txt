# Set Project_Name and Language
set(PROJECT_NAME "dbengine")
project(${PROJECT_NAME} CXX)

# version 2.8.12 is on unix.cse.tamu.edu
cmake_minimum_required(VERSION 2.8.12)

# can't run if build.sh hasn't been run
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.buildshran")
  message("build.sh must run before cmake. Running build.sh now")
  execute_process(COMMAND bash build.sh WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
  message("build.sh must run before cmake. Ran build.sh for you")
  message(FATAL_ERROR "cmake will now exit")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -DDEBUG -Wall -Wextra")

# Unit testing with Google Test
# to run tests use 'cmake -Dtest=ON'
option(test "Build ${PROJECT_NAME}'s tests" OFF)

# set some locations
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

if(APPLE)
  # do nothing
elseif(UNIX)
  set(Boost_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include/boost")
endif()

# include directories
include_directories(${LIB_DIR} ${Boost_INCLUDE_DIRS})
# if testing include gtest
if (test)
  add_subdirectory(${INCLUDES_DIR}/gtest)
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

# set names
set(RELEASE_BINARY "main")
set(RELEASE_BINARY_OUTNAME "${PROJECT_NAME}")
set(UNITTEST_BINARY "${PROJECT_NAME}test")
set(ENGINE_LIBRARY "${PROJECT_NAME}")

# add directory for project source files and libraries
add_subdirectory(${SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
add_subdirectory(${LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/lib)
