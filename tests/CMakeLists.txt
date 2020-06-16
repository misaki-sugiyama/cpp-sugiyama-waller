cmake_minimum_required(VERSION 3.14.5)
project(sugiyama-waller-test LANGUAGES CXX)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
  message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()

## To enforce c++17 usage when building catch2
set(CMAKE_CXX_STANDARD 17 CACHE INTERNAL "CMAKE_CXX_STANDARD")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "CMAKE_CXX_STANDARD_REQUIRED") # c++17 is required
set(CMAKE_CXX_EXTENSIONS OFF CACHE INTERNAL "CMAKE_CXX_EXTENSIONS") # use -std=c++* instead of -std=gnu++*

add_subdirectory(.. orig)
add_subdirectory(deps/catch2)

file(GLOB srcs LIST_DIRECTORIES true CONFIGURE_DEPENDS test-*.cc)

add_executable(test-program ${srcs})
target_link_libraries(test-program sugiyama-waller)
target_link_libraries(test-program Catch2::Catch2WithMain)

add_custom_target(test COMMAND $<TARGET_FILE:test-program> --use-colour yes DEPENDS test-program)
