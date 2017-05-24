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

FILE(GLOB HEADERS "${PROJECT_SOURCE_DIR}/stdplus/*.h")
SET(HEADERS ${HEADERS} "${PROJECT_BINARY_DIR}/stdplus/version.h")

install(TARGETS stdplus DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/stdplus)

add_executable(app main.c)
target_link_libraries(app stdplus)

