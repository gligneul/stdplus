cmake_minimum_required(VERSION 2.6)
project(stdplus)

set(STDPLUS_VERSION_MAJOR 0)
set(STDPLUS_VERSION_MINOR 1)
configure_file(
  "${PROJECT_SOURCE_DIR}/include/stdplus/version.h.in"
  "${PROJECT_BINARY_DIR}/include/stdplus/version.h")

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
  src/mem.c)

SET(stdplus_headers ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR}/include)
target_include_directories(stdplus PUBLIC ${stdplus_headers})
include_directories(${stdplus_headers})

install(TARGETS stdplus DESTINATION lib)
install(DIRECTORY ${stdplus_headers} DESTINATION include)

if(ENABLE_STDPLUS_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif(ENABLE_STDPLUS_TESTS)

