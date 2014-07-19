cmake_minimum_required(VERSION 2.8.9)
cmake_policy(SET CMP0020 NEW)

set(GCC_COMP_FLAGS "-static-libgcc -static-libstdc++ -std=gnu++0x -fopenmp")
if(WIN_BUILD)
set(GCC_COMP_FLAGS "${GCC_COMP_FLAGS} -mwindows")
endif(WIN_BUILD)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMP_FLAGS}")
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
find_program(CMAKE_CXX_COMPILER g++)
find_program(CMAKE_C_COMPILER gcc)

project(StellaEngine)

#Versioning
set(Engine_Major_Version 0)
set(Engine_Minor_Version 0)
set(Engine_Patch 040)																				#Handled by build script
set(DevRelease ${DevRelease} CACHE BOOL "Set to Y if Development Build; N otherwise" FORCE)
set(WIN_BUILD ${WIN_BUILD} CACHE BOOL "Set to Y if Development Build; N otherwise" FORCE)

if(WIN_BUILD)
set(WIN_BUILD true)
else(WIN_BUILD)
set(WIN_BUILD false)
endif(WIN_BUILD)

set(Engine_Version ${Engine_Major_Version}.${Engine_Minor_Version}.${Engine_Patch})
if(DevRelease)
set(Engine_Version "${Engine_Version} DEV")
endif(DevRelease)

#Create Config
configure_file("${PROJECT_SOURCE_DIR}/EngineConfig.h.in" "${PROJECT_BINARY_DIR}/EngineConfig.h")
include_directories("${PROJECT_BINARY_DIR}")

#Create subdirs
#add_subdirectory(assets)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory modules)
#install(CODE "file(make_directory \${ENV}\${CMAKE_INSTALL_PREFIX}\${modules})")

#List Sources
set(SOURCE_FILES main.cpp processes/ModuleFramework/modLoad.cpp processes/ObjectFramework/objFrame.cpp)

#Add Debugging information (DevReleases)
if(DevRelease)
set(CMAKE_BUILD_TYPE "Debug")
else(DevRelease)
set(CMAKE_BUILD_TYPE "Release")
endif(DevRelease)

#Create Execs
if(DevRelease)
add_executable(StellaEngine-EX ${SOURCE_FILES})
target_link_libraries(StellaEngine-EX ${CMAKE_DL_LIBS})
else(DevRelease)
add_executable(StellaEngine ${SOURCE_FILES})
target_link_libraries(StellaEngine ${CMAKE_DL_LIBS})
endif(DevRelease)
