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

SET(HEADERS
  "${PROJECT_SOURCE_DIR}/stdplus/*.h"
  "${PROJECT_BINARY_DIR}/stdplus/version.h")

install(TARGETS stdplus DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/stdplus)

include(CTest)
enable_testing()
add_custom_target(build-tests)
add_executable(vectest EXCLUDE_FROM_ALL tests/vectest.c)
add_dependencies(build-tests vectest)
target_link_libraries(vectest stdplus)
add_test(vectest vectest)

