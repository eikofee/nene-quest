cmake_minimum_required(VERSION 3.5)

project( NeneQuest )

# Headers location
include_directories( headers )


#Prepare executable
set(EXECUTABLE_NAME "NeneQuest")
# Sources locations
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable( ${EXECUTABLE_NAME} ${SOURCES} )


# Compiler Flag
SET(CXX_FLAGS "-std=c++11")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}" )


# Detect and add SFML
set(CMAKE_MODULE_PATH "cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()





