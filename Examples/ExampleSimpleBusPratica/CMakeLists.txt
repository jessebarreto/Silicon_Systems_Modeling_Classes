
add_executable(SimpleBusPratica
               simple_bus_main.cpp
               simple_bus.cpp
#               simple_bus.h
               simple_bus_arbiter.cpp
               simple_bus_arbiter_if.h
               simple_bus_blocking_if.h
               simple_bus_direct_if.h
               simple_bus_fast_mem.h
               simple_bus_non_blocking_if.h
               simple_bus_request.h
               simple_bus_slave_if.h
               simple_bus_slow_mem.h
               simple_bus_custom_mem.h
               simple_bus_test.h
               simple_bus_master_blocking.cpp
               simple_bus_master_direct.cpp
               simple_bus_master_non_blocking.cpp
               simple_bus_tools.cpp
               simple_bus_types.cpp
               )
target_link_libraries(SimpleBusPratica ${SYSTEMC_LIBRARIES})
