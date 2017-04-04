
#add_executable(ThreeStateBuses threestatebusexample.cpp
#    threestatebusreg.h
#    threestatebusregtb.h
#    threestatebusregenable.h
#    threestatebusregenabletb.h
#    threestatebus.h
#    threestatebustb.h
#    )
#target_link_libraries(ThreeStateBuses ${SYSTEMC_LIBRARIES})

add_executable(ThreeStateBus threestatebusexample.cpp threestatebus.h threestatebustb.h)
target_link_libraries(ThreeStateBus ${SYSTEMC_LIBRARIES})

add_executable(ThreeStateBusReg threestatebusregexample.cpp threestatebusreg.h threestatebusregtb.h)
target_link_libraries(ThreeStateBusReg ${SYSTEMC_LIBRARIES})

add_executable(ThreeStateBusRegEnable threestatebusregenableexample.cpp threestatebusregenable.h threestatebusregenabletb.h)
target_link_libraries(ThreeStateBusRegEnable ${SYSTEMC_LIBRARIES})
