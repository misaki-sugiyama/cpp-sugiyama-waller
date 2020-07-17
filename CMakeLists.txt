cmake_minimum_required(VERSION 3.14.5)
project (sugiyama-waller LANGUAGES CXX)

include(sugiyama.cmake)
sugiyama_no_indir()

file(GLOB_RECURSE hdrs LIST_DIRECTORIES true CONFIGURE_DEPENDS src/sugiyama/*.h)
file(GLOB_RECURSE srcs LIST_DIRECTORIES true CONFIGURE_DEPENDS src/sugiyama/*.cc)
add_library(${PROJECT_NAME} STATIC ${srcs})
target_sources(${PROJECT_NAME} INTERFACE ${hdrs})
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

## Deps: magnum-singles
target_include_directories(${PROJECT_NAME} PUBLIC deps/magnum-singles)
