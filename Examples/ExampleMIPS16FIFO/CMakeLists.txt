
add_executable(MIPS16FIFO main.cpp
               sistema.h
               fetch.h
               decode.h
               execute.h
               memoryblock.h
               estado.h)
target_link_libraries(MIPS16FIFO ${SYSTEMC_LIBRARIES})

