include(CTest)

add_executable(vectest vectest.c)
target_link_libraries(vectest stdplus)
add_test(vectest vectest)

