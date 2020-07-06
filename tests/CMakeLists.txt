cmake_minimum_required(VERSION 3.14.5)
project(sugiyama-waller-test LANGUAGES CXX)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
  message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()

## To enforce c++17 usage when building catch2
set(CMAKE_CXX_STANDARD 17 CACHE INTERNAL "CMAKE_CXX_STANDARD")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "CMAKE_CXX_STANDARD_REQUIRED") # c++17 is required
set(CMAKE_CXX_EXTENSIONS OFF CACHE INTERNAL "CMAKE_CXX_EXTENSIONS") # use -std=c++* instead of -std=gnu++*

## To enforce colorized output on terminal for Ninja
## https://medium.com/@alasher/colored-c-compiler-output-with-ninja-clang-gcc-10bfe7f2b949
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." FALSE)
if (${FORCE_COLORED_OUTPUT})
  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always" CACHE INTERNAL "CMAKE_CXX_FLAGS")
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics" CACHE INTERNAL "CMAKE_CXX_FLAGS")
  endif ()
endif ()

add_subdirectory(.. orig)
add_subdirectory(deps/catch2)

file(GLOB srcs LIST_DIRECTORIES true CONFIGURE_DEPENDS *.cc */*.cc */*.h)

add_executable(test-program ${srcs})
target_link_libraries(test-program sugiyama-waller)
target_link_libraries(test-program Catch2::Catch2WithMain)

add_custom_target(test COMMAND $<TARGET_FILE:test-program> --use-colour yes DEPENDS test-program)
