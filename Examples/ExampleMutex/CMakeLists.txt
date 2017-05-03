
add_executable(Mutex mutexexample.cpp mutex.h)
target_link_libraries(Mutex ${SYSTEMC_LIBRARIES})
