cmake_minimum_required(VERSION 3.14.5)
project(sugiyama-waller-test LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../sugiyama.cmake)
sugiyama_no_indir_recursive()

## To enforce c++17 usage when building catch2
sugiyama_force_cxx17()

## To enforce colorized output on terminal for Ninja
sugiyama_color_cc()

add_subdirectory(.. orig)
add_subdirectory(deps/catch2)

file(GLOB srcs LIST_DIRECTORIES true CONFIGURE_DEPENDS *.cc */*.cc */*.h)

add_executable(test-program ${srcs})
target_link_libraries(test-program sugiyama-waller)
target_link_libraries(test-program Catch2::Catch2WithMain)

add_custom_target(test COMMAND $<TARGET_FILE:test-program> --use-colour yes DEPENDS test-program)
