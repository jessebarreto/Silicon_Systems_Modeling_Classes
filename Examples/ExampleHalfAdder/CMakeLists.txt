
add_executable(HalfAdderExample halfadderexample.cpp hf_adder.h hf_adder_testbench.h)
target_link_libraries(HalfAdderExample ${SYSTEMC_LIBRARIES})

