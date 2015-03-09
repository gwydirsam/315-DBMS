# version 2.8.12 is on unix.cse.tamu.edu
cmake_minimum_required(VERSION 2.8.12)

# Set Project_Name and Language
project(dbapp CXX)

# set compilation variables
if(${CMAKE_COMPILER_IS_GNUCXX})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -DDEBUG -Wall -Wextra")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -stdlib=libc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -DDEBUG -Wall -Wextra")
endif()

if(APPLE)
  # do nothing
elseif(UNIX)
  set(BOOST_ROOT ~/usr/)
  # set(Readline_ROOT_DIR /opt/csw/)
endif()

# Unit testing with Google Test
# to run tests use 'cmake -Dtest=ON'
option(test "Build ${PROJECT_NAME}'s tests" OFF)

# set some locations
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDES_DIR "${CMAKE_SOURCE_DIR}/include")
set(CMAKE_MODULE_PATH ${INCLUDES_DIR})
set(Readline_DIR ${INCLUDES_DIR})
if (test)
  add_subdirectory(${INCLUDES_DIR}/gtest)
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

set(GROUP16_LIBRARY "group16dbms")
#include_directories("${INCLUDES_DIR}/Group16DBMS")
add_subdirectory("${INCLUDES_DIR}/Group16DBMS")
find_library(GROUP16DBMS NAMES ${GROUP16_LIBRARY} libgroup16dbms HINTS "${CMAKE_SOURCE_DIR}/lib/group16dbms")


# add directory for project source files
add_subdirectory(${SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
