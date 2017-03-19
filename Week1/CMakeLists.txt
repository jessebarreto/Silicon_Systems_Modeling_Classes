
# Executable for the 1st week
add_executable(begin begin.cpp)
target_link_libraries(begin ${SYSTEMC_LIBRARIES})

add_executable(counter_testbench counter_testbench.cpp counter.cpp)
target_link_libraries(counter_testbench ${SYSTEMC_LIBRARIES})

