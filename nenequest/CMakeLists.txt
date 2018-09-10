cmake_minimum_required(VERSION 3.5)

project( NeneQuest )

# Headers location
include_directories( headers )


#Prepare executable
set(EXECUTABLE_NAME "NeneQuest.exe")
# Sources locations
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable( ${EXECUTABLE_NAME} ${SOURCES} )


# Compiler Flag
SET(CXX_FLAGS "-std=c++11")
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CXX_FLAGS}" )


## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio)
