cmake_minimum_required(VERSION 2.8)
project(StellaEngine)

#Versioning
set(Engine_Major_Version 0)
set(Engine_Minor_Version 0)
set(Engine_Build 1)
set(Engine_Version ${Engine_Major_Version}.${Engine_Minor_Version}.${Engine_Build})

#Create Config
configure_file("${PROJECT_SOURCE_DIR}/EngineConfig.h.in" "${PROJECT_BINARY_DIR}/EngineConfig.h")
include_directories("${PROJECT_BINARY_DIR}")

#Include subdirs
add_subdirectory(headers)
add_subdirectory(processes)
add_subdirectory(launcher)
add_executable(StellaEngine main.cpp)
