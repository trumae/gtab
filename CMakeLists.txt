cmake_minimum_required (VERSION 2.6) 
project (GTAB)
set (GTAB_VERSION_MAJOR 0)
set (GTAB_VERSION_MINOR 1)

configure_file (
  "${PROJECT_SOURCE_DIR}/GTABConfig.h.in"
  "${PROJECT_BINARY_DIR}/GTABConfig.h"
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -ggdb -std=c++11 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c++11 -O2")

add_subdirectory (src)

