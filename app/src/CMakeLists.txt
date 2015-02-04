set(SRCS
	)

set(MAIN_SRC main.cc)

set(UNITTEST_SRCS
  test_main.cc)

set(DEBUG_OBJECT_LIBRARY "debug_objects")
set(DEBUG_BINARY "${PROJECT_NAME}d")
set(RELEASE_BINARY "${PROJECT_NAME}")
set(UNITTEST_BINARY "${PROJECT_NAME}unittest")

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${gtest_INCLUDE_DIR})

add_library(${DEBUG_OBJECT_LIBRARY} OBJECT ${SRCS})
add_executable(${DEBUG_BINARY}
	${MAIN_SRC}
	$<TARGET_OBJECTS:${DEBUG_OBJECT_LIBRARY}>)
add_executable(${RELEASE_BINARY} ${MAIN_SRC} ${SRCS})

set_property(SOURCE ${SRCS} PROPERTY COMPILE_FLAGS "${CXXFLAGS_DEBUG}")
set_target_properties(${DEBUG_BINARY} PROPERTIES COMPILE_FLAGS "${CXXFLAGS_DEBUG}")
set_target_properties(${RELEASE_BINARY} PROPERTIES COMPILE_FLAGS "${CXXFLAGS_RELEASE}")
target_link_libraries(${DEBUG_BINARY})
target_link_libraries(${RELEASE_BINARY})

# Testing
if (test)
  # add gtest
  add_subdirectory(${INCLUDES_DIR}/gtest)

  enable_testing()

  # Include the gtest library. gtest_SOURCE_DIR is available due to
  # 'project(gtest)' above.
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  # Unit Tests
	add_executable(${UNITTEST_BINARY}
		${UNITTEST_SRCS}
		$<TARGET_OBJECTS:${DEBUG_OBJECT_LIBRARY}>)

  # Standard linking to gtest stuff.
	set_target_properties(${UNITTEST_BINARY} PROPERTIES COMPILE_FLAGS "${CXXFLAGS_DEBUG}")
	target_link_libraries(${UNITTEST_BINARY} gtest gtest_main)

  # This is so you can do 'make test' to see all your tests run, instead of
  # manually running the executable runUnitTests to see those specific tests.
  add_test(NAME that-test-I-made COMMAND ${UNITTEST_BINARY})

  # You can also omit NAME and COMMAND. The second argument could be some other
  # test executable.
  add_test(that-other-test-I-made ${UNITTEST_BINARY})
endif()
