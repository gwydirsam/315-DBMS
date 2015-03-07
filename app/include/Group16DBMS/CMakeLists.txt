# Set Project_Name and Language
project(group16dbms CXX)

# version 2.8.12 is on unix.cse.tamu.edu
cmake_minimum_required(VERSION 2.8.12)

if(${CMAKE_COMPILER_IS_GNUCXX})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -DDEBUG -Wall -Wextra")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -stdlib=libc++")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb -O0 -DDEBUG -Wall -Wextra")
endif()

set(MAIN
  DBShell.cpp
  )

set(SRCS
Conditions.cpp
Database.cpp
Parser.cpp
Table.cpp
	)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME}shell ${MAIN} ${SRCS})
add_library(${PROJECT_NAME} SHARED ${SRCS})

#use C++14
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.0 SOVERSION 1)