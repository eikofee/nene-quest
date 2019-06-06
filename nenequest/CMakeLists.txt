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
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} sfml-graphics sfml-audio)

include(GNUInstallDirs)
install(DIRECTORY bgm fonts img levels sfx
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${EXECUTABLE_NAME})
install(FILES config/config.ini
  DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${EXECUTABLE_NAME})
install(TARGETS ${EXECUTABLE_NAME}
  DESTINATION ${CMAKE_INSTALL_BINDIR})

# Package Generator
include(CPack)
