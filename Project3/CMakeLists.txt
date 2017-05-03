
add_executable(Project3 main.cpp
               sistema.h
               driver.h
               multiplier.h
               monitor.h
              )
target_link_libraries(Project3 ${SYSTEMC_LIBRARIES})

