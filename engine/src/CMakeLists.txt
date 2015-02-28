set(MAIN_SRC main.cc)

set(UNITTEST_SRCS
  test_main.cc)

#find_package(Boost 1.57.0)
#include_directories(${Boost_INCLUDE_DIRS})

set(RELEASE_BINARY "main")
set(RELEASE_BINARY_OUTNAME "${PROJECT_NAME}")
set(UNITTEST_BINARY "${PROJECT_NAME}test")
set(ENGINE_LIBRARY "${PROJECT_NAME}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${RELEASE_BINARY} ${MAIN_SRC})

#use C++14
set_property(TARGET ${RELEASE_BINARY} PROPERTY CXX_STANDARD 14)
#C++14 required
#set_property(TARGET ${RELEASE_BINARY} PROPERTY CXX_STANDARD_REQUIRED ON)

set_target_properties(${RELEASE_BINARY} PROPERTIES OUTPUT_NAME "${RELEASE_BINARY_OUTNAME}")

#target_link_libraries(${RELEASE_BINARY} ${ENGINE_LIBRARY} ${Boost_LIBRARIES})
target_link_libraries(${RELEASE_BINARY} ${ENGINE_LIBRARY})

# Testing
if (test)
  enable_testing()

  # Unit Tests
	add_executable(${UNITTEST_BINARY} ${UNITTEST_SRCS})

  # Standard linking to gtest stuff.
	target_link_libraries(${UNITTEST_BINARY} ${ENGINE_LIBRARY} gtest gtest_main)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME that-test-I-made COMMAND ${UNITTEST_BINARY})

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  add_test(that-other-test-I-made ${UNITTEST_BINARY})
endif()
