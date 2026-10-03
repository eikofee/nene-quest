cmake_minimum_required(VERSION 3.21)
project(NeneQuest LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Generate compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

## SFML: use an installed SFML 2.6 if there is one, otherwise download it
find_package(SFML 2.6 COMPONENTS graphics audio QUIET)
if(NOT SFML_FOUND)
  message(STATUS "SFML 2.6 not found, downloading it")
  include(FetchContent)
  set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON)
  FetchContent_MakeAvailable(SFML)
endif()

## Executable
# CONFIGURE_DEPENDS makes new .cpp files get picked up without re-running cmake
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(NeneQuest ${SOURCES})
target_include_directories(NeneQuest PRIVATE headers)
target_compile_features(NeneQuest PRIVATE cxx_std_17)
target_link_libraries(NeneQuest PRIVATE sfml-graphics sfml-audio)

if(MSVC)
  target_compile_options(NeneQuest PRIVATE /W4)
  target_compile_definitions(NeneQuest PRIVATE _USE_MATH_DEFINES) # M_PI
else()
  target_compile_options(NeneQuest PRIVATE -Wall -Wextra -Wsuggest-override
    $<$<CONFIG:Debug>:-fsanitize=undefined>)
  target_link_options(NeneQuest PRIVATE $<$<CONFIG:Debug>:-fsanitize=undefined>)
endif()

# On Windows, copy the SFML DLLs next to the executable so it runs from build/
if(WIN32)
  add_custom_command(TARGET NeneQuest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      $<TARGET_RUNTIME_DLLS:NeneQuest> $<TARGET_FILE_DIR:NeneQuest>
    COMMAND_EXPAND_LISTS)
endif()
