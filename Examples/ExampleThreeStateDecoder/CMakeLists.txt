
add_executable(ThreeStateDecoder threestatedecoderexample.cpp threestatedecoder.h threestatedecodertb.h)
target_link_libraries(ThreeStateDecoder ${SYSTEMC_LIBRARIES})
