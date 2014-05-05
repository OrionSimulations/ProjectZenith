cmake_minimum_required(VERSION 2.8.9)
cmake_policy(SET CMP0020 NEW)
if(WIN32)
set(WIN_LIB_DIR "C:/ProjectLibs")
link_directories(${WIN_LIB_DIR}/lib)
endif(WIN32)
set(GCC_COMP_FLAGS "-static-libgcc -static-libstdc++ -std=gnu++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMP_FLAGS}")
find_program(CMAKE_CXX_COMPILER g++)
find_program(CMAKE_C_COMPILER gcc)

project(StellaEngine - Communications)

set(Module_Major_Version 0)
set(Module_Minor_Version 0)
set(Module_Patch 000)
set(DevRelease Y)                                                                                   #DevRelease? NOTE: After changing, rerun CMake to cache the change
set(Module_Version ${Module_Major_Version}.${Module_Minor_Version}.${Module_Patch})
if(DevRelease)
set(Module_Version "${Module_Version} DEV")
endif(DevRelease)

#Create Config
configure_file("${PROJECT_SOURCE_DIR}/ModuleConfig.cfg.in" "${PROJECT_BINARY_DIR}/ModuleConfig.cfg")
include_directories("${PROJECT_BINARY_DIR}")

#Create Execs
if(DevRelease)
add_executable(Communications-Experimental CommMain.cpp)
else(DevRelease)
add_executable(Communications CommMain.cpp)
endif(DevRelease)