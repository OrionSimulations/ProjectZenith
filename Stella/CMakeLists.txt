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
set(Engine_Patch 072)																				#Handled by build script
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

#List Sources
set(LIB_FILES ModuleFramework/modLoad.cpp AssetFramework/objFrame.cpp stella.cpp contentLoad.cpp)

#Add Debugging information (DevReleases)
if(DevRelease)
set(CMAKE_BUILD_TYPE "Debug")
else(DevRelease)
set(CMAKE_BUILD_TYPE "Release")
endif(DevRelease)

#Create Execs
add_library(Stella ${LIB_FILES})
target_link_libraries(Stella ${CMAKE_DL_LIBS})

install(TARGETS Stella ARCHIVE DESTINATION lib)
install(FILES stella.h DESTINATION include/Stella)
install(FILES FindStella.cmake DESTINATION /usr/share/cmake-2.8/Modules/)