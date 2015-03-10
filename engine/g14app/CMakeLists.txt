set(MAIN_SRC db_app.cpp)

set(RELEASE_BINARY "g14app")
set(ENGINE_LIBRARY "${PROJECT_NAME}")

find_package(Boost 1.57.0 COMPONENTS filesystem system REQUIRED)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${RELEASE_BINARY} ${MAIN_SRC})

#use C++14
set_property(TARGET ${RELEASE_BINARY} PROPERTY CXX_STANDARD 14)
#C++14 required
#set_property(TARGET ${RELEASE_BINARY} PROPERTY CXX_STANDARD_REQUIRED ON)

# if(CURSES_FOUND)
#   target_link_libraries(${RELEASE_BINARY} ${ENGINE_LIBRARY} ${Boost_LIBRARIES}  ${Readline_LIBRARY} ${CURSES_LIBRARIES})
# elseif(READLINE_FOUND)
#   target_link_libraries(${RELEASE_BINARY} ${ENGINE_LIBRARY} ${Boost_LIBRARIES}  ${Readline_LIBRARY})
# else()
   #target_link_libraries(${RELEASE_BINARY} ${ENGINE_LIBRARY} ${Boost_LIBRARIES})
# endif()
target_link_libraries(${RELEASE_BINARY} ${ENGINE_LIBRARY} ${Boost_LIBRARIES})
#target_link_libraries(${RELEASE_BINARY} ${ENGINE_LIBRARY})