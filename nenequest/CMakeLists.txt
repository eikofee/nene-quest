cmake_minimum_required(VERSION 3.8)
project(NeneQuest)

# Headers location
include_directories(headers)

# Prepare executable
set(EXECUTABLE_NAME "NeneQuest")

# Sources locations
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_compile_options(${EXECUTABLE_NAME} PRIVATE -Wall)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "thirdparty/sfml/lib/cmake/SFML")

find_package(SFML REQUIRED COMPONENTS graphics audio)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio)
install(FILES $<TARGET_RUNTIME_DLLS:NeneQuest> TYPE BIN)
install(FILES "thirdparty/sfml/bin/openal32.dll" TYPE BIN)

install(DIRECTORY bgm fonts img levels sfx DESTINATION bin)
install(FILES config/config.ini DESTINATION bin)
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# Package Generator
include(CPack)
