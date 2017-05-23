#######################################################################
#
# THIS FILE MAKES THE COMPILATION OF CODE DEVELOPED IN THIS SEMESTER AUTOMATIC.
# BY jesseh.barreto@gmail.com
#
#
# TO USE JUST ADD A NEW SUB_DIRECTORY WITH A CMAKELIST.TXT INSIDE.
# WITH:
#       add_subdirectory(dir_name)
#       add_executable(bin_name source_code)
#       target_link_libraries(bin_name libraries)
#
#######################################################################

project(Silicon_Systems_Modeling_Classes)
cmake_minimum_required(VERSION 2.8)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Find SystemC
set(SYSTEMC_HOME /home/jesseh/libs/systemc-2.3.1a)
include_directories(SYSTEM "${SYSTEMC_HOME}/include")
set(SYSTEMC_LIBRARIES ${SYSTEMC_HOME}/lib-linux64/libsystemc.a ${SYSTEMC_HOME}/lib-linux64/libsystemc-2.3.1.so)
set (CMAKE_CXX_FLAGS "-pthread")

# Subdirectories
add_subdirectory(Exercicio1)
add_subdirectory(Week1)
add_subdirectory(Project1)
add_subdirectory(Project2)
add_subdirectory(Project3)
add_subdirectory(Project4)
add_subdirectory(Examples)

# Old Noc
#add_subdirectory(OldNoC)
