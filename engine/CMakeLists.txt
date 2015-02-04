cmake_minimum_required(VERSION 2.8.12)

# Set Project_Name and Language
set(PROJECT_NAME "dbengine")
project(${PROJECT_NAME} CXX)

# Unit testing with Google Test
# to run tests use 'cmake -Dtest=ON'
option(test "Build ${PROJECT_NAME}'s tests" OFF)

# set some locations
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(COMMON_INCLUDES "${SOURCE_DIR}/include")

# add directory for project source files
add_subdirectory(${SOURCE_DIR})

# set compilation variables
set(CXXFLAGS "-Wall -Wextra -std=c++14")
set(CXXFLAGS_RELEASE "${CXXFLAGS} -O3 -DNDEBUG")
set(CXXFLAGS_DEBUG "${CXXFLAGS} -g -O0 -DDEBUG")

# Testing
if (test)
  # add gtest
  add_subdirectory(${COMMON_INCLUDES}/gtest)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  # Unit Tests
  add_executable(runUnitTests test_main.cc)

  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests gtest gtest_main)

  # Extra linking for the project.
  # TODO: Fix Later
  #target_link_libraries(runUnitTests project1_lib)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME that-test-I-made COMMAND runUnitTests)

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  add_test(that-other-test-I-made runUnitTests)
endif()