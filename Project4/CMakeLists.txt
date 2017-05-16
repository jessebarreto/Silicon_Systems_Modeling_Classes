
add_executable(RISC16_Req1
                main1.cpp
                shared.h
                sistema1.h
                risc16threads.h)
target_link_libraries(RISC16_Req1 ${SYSTEMC_LIBRARIES})

add_executable(RISC16_Req2
                main2.cpp
                shared.h
                sistema1.h
                risc16threads.h
                sistema2.h
                ibusmaster.h
                ibusslave.h
                bus.h
                fetch.h
                decode.h
                execute.h
                memoryblock.h
                registerblock.h
                estado.h)
target_link_libraries(RISC16_Req2 ${SYSTEMC_LIBRARIES})
