
add_executable(OldNoC
                main.cpp
                cod.cpp
            	decod.cpp
            	kernel_ni.cpp
                router.cpp
                full_router.h
                master.h
                noc_common.h
                shell_master_ni.h
                shell_slave_ni.h
                slave.h
                MIPS/globals.h
                MIPS/memoria.h
                MIPS/mips.h
                MIPS/shell_mips.h
                MIPS/shell_memoria.cpp
                )
target_link_libraries(OldNoC ${SYSTEMC_LIBRARIES})
