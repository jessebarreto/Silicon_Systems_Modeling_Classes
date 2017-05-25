
add_executable(ExampleNoC
               main.cpp
               cod.cpp
               decod.cpp
               kernel_ni.cpp
               router.cpp
               master.h
               slave.h
               noc_common.h
               shell_master_ni.h
               shell_slave_ni.h
               )
target_link_libraries(ExampleNoC ${SYSTEMC_LIBRARIES})
