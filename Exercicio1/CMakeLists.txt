
add_executable(full_adder_1bit_tb main.cpp fa.cpp ha_sc.cpp contorno.cpp)
target_link_libraries(full_adder_1bit_tb ${SYSTEMC_LIBRARIES})
