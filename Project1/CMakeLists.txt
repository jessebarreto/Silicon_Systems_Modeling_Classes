
add_executable(ula_main main.cpp sistema.h ula.cpp ula_tb.cpp)
target_link_libraries(ula_main ${SYSTEMC_LIBRARIES})
