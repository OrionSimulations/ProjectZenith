cmake_minimum_required(VERSION 2.8.9)
cmake_policy(SET CMP0020 NEW)
set(GCC_COMP_FLAGS "-static-libgcc -static-libstdc++ -std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMP_FLAGS} ")
set(CMAKE_CXX_COMPILER C:/MinGW/bin/g++.exe)
set(CMAKE_C_COMPILER C:/MinGW/bin/gcc.exe)

project(StellaEngine)

#Versioning
set(Engine_Major_Version 0)
set(Engine_Minor_Version 0)
set(Engine_Build 002)
set(DevRelease Y)                                                                                   #DevRelease? NOTE: After changing, rerun CMake to cache the change.
set(Engine_Version ${Engine_Major_Version}.${Engine_Minor_Version}.${Engine_Build})

#Create Config
configure_file("${PROJECT_SOURCE_DIR}/EngineConfig.h.in" "${PROJECT_BINARY_DIR}/EngineConfig.h")
include_directories("${PROJECT_BINARY_DIR}")

#Include subdirs
add_subdirectory(headers)
add_subdirectory(processes)
add_subdirectory(launcher)

#Include Qt Resources. Prefer standard OpenGL usage, but left as an option.
#set(QtComp Core Widgets)                                                                            #Add to this list as requirements are updated
#set(CMAKE_PREFIX_PATH C:/Qt/5.2.0/Src/qtbase/include)
#set(CMAKE_INCLUDE_PATH C:/Qt/5.2.0/Src/qtbase/include)
#find_package(Qt5 REQUIRED COMPONENTS ${QtComp})
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)

#Create Execs
if(NOT DevRelease)
add_executable(StellaEngine stable.cpp)
else(NOT DevRelease)
add_executable(StellaEngine dev.cpp)
endif(NOT DevRelease)

#Link Launcher Libraries
add_executable(Launcher runLauncher.cpp)
#qt5_use_modules(Launcher ${QtComp})                                                                #Enable if using Qt Libraries for Launcher Interface
