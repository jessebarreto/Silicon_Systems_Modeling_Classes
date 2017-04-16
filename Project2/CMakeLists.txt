
add_executable(Project2 main.cpp
        sistema.h
        sistema2.h
        temporizador.cpp
        drivertb.cpp
        printertb.cpp
        fsmsemaforo3methods.cpp
        fsmsemaforo2methods.cpp
    )
target_link_libraries(Project2 ${SYSTEMC_LIBRARIES})

