cmake_minimum_required(VERSION 2.6)
project(stdplus)

set(STDPLUS_VERSION_MAJOR 0)
set(STDPLUS_VERSION_MINOR 1)
configure_file(
  "${PROJECT_SOURCE_DIR}/stdplus/version.h.in"
  "${PROJECT_BINARY_DIR}/stdplus/version.h")

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_BINARY_DIR}")

add_definitions(
  -std=c89
  -Wall
  -Wextra
  -Werror
  -Wundef
  -Wshadow
  -Wcast-align
  -Wstrict-prototypes
  -Wmissing-prototypes
  -pedantic)

add_library(stdplus
  stdplus/mem.c)

SET(stdplus_headers
  "${PROJECT_SOURCE_DIR}/stdplus/*.h"
  "${PROJECT_BINARY_DIR}/stdplus/version.h")

install(TARGETS stdplus DESTINATION lib)
install(FILES ${stdplus_headers} DESTINATION include/stdplus)

if(ENABLE_STDPLUS_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(ENABLE_STDPLUS_TESTS)

