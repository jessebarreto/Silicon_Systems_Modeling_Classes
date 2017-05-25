
add_executable(OldNoC
                main.cpp
                cod.cpp
                cod.h
            	decod.cpp
                decod.h
            	kernel_ni.cpp
                kernel_ni.h
                router.cpp
                full_router.h
                master.h
                noc_common.h
                shell_master_ni.h
                shell_slave_ni.h
                slave.h
                MIPS/globals.h
                MIPS/memdef.h
                MIPS/mem_if.h
                MIPS/memoria.cpp
                MIPS/memoria.h
                MIPS/mips.cpp
                MIPS/mips.h
                MIPS/shell_mips.cpp
                MIPS/shell_mips.h
                MIPS/shell_memoria.h
                )
target_link_libraries(OldNoC ${SYSTEMC_LIBRARIES})
