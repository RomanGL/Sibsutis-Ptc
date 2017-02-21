cmake_minimum_required(VERSION 3.6)
project(Sibsutis_Ptc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../output/lib)

###### HwThreads ######
set(HWTHREADS_SOURCE HwThreads/main.c)
add_executable(HwThreads ${HWTHREADS_SOURCE})
###### HwThreads ######

###### HwNThreads ######
set(HW_N_THREADS_SOURCE HwNThreads/main.c)
add_executable(HwNThreads ${HW_N_THREADS_SOURCE})
###### HwNThreads ######

###### IntegrateMidpoint ######
set(INTEGRATE_MIDPOINT_SOURCE IntegrateMidpoint/main.c)
add_executable(IntegrateMidpoint ${INTEGRATE_MIDPOINT_SOURCE})
###### IntegrateMidpoint ######

###### IntegrateMidpointThreads ######
set(INTEGRATE_MIDPOINT_THREADS_SOURCE IntegrateMidpointThreads/main.c)
add_executable(IntegrateMidpointThreads ${INTEGRATE_MIDPOINT_THREADS_SOURCE})
###### IntegrateMidpointThreads ######