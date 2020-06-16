cmake_minimum_required(VERSION 3.14.5)
project (sugiyama-waller LANGUAGES CXX)

if (CMAKE_CURRENT_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_CURRENT_SOURCE_DIR}/CMakeCache.txt")
endif()

file(GLOB_RECURSE srcs LIST_DIRECTORIES true CONFIGURE_DEPENDS src/sugiyama/*.h)
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${srcs})
target_include_directories(${PROJECT_NAME} INTERFACE src)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
