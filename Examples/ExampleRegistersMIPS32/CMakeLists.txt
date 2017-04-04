
add_executable(RegistersMIPS32 registersmips32example.cpp registersmips32.h registersmips32tb.h)
target_link_libraries(RegistersMIPS32 ${SYSTEMC_LIBRARIES})
