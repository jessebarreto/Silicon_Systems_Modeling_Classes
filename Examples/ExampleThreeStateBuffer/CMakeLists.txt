
add_executable(ThreeStateBuffer threestatebufferexample.cpp threestatebuffer.h threestatebuffertb.h)
target_link_libraries(ThreeStateBuffer ${SYSTEMC_LIBRARIES})
