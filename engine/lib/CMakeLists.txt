set(SRCS
  utility.cc
  relation.cc
  engine.cc
  grammar.cc
  grammar_objects/condition.cc
  grammar_objects/expression.cc
  grammar_objects/command.cc
  grammar_objects/query.cc
  grammar_objects/program.cc
	)

find_package(Boost 1.57.0 COMPONENTS filesystem system)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/grammar_objects)

set(ENGINE_LIBRARY "dbengine")

add_library(${ENGINE_LIBRARY} SHARED ${SRCS})
target_link_libraries(${ENGINE_LIBRARY} ${Boost_LIBRARIES})

#use C++14
set_property(TARGET ${ENGINE_LIBRARY} PROPERTY CXX_STANDARD 14)
#C++14 required
#set_property(TARGET ${ENGINE_LIBRARY} PROPERTY CXX_STANDARD_REQUIRED ON)

#set_target_properties(${ENGINE_LIBRARY} PROPERTIES COMPILE_FLAGS "${CXXFLAGS_RELEASE}")
#set_target_properties(${ENGINE_LIBRARY_DEBUG} PROPERTIES COMPILE_FLAGS "${CXXFLAGS_DEBUG}")
set_target_properties(${ENGINE_LIBRARY} PROPERTIES VERSION 1.0.0 SOVERSION 1)
