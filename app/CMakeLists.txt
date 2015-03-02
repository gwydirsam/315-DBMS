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

# Unit testing with Google Test
# to run tests use 'cmake -Dtest=ON'
option(test "Build ${PROJECT_NAME}'s tests" OFF)

# set some locations
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDES_DIR "${CMAKE_SOURCE_DIR}/include")
if (test)
  add_subdirectory(${INCLUDES_DIR}/gtest)
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
endif()

# add directory for project source files
add_subdirectory(${SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})
