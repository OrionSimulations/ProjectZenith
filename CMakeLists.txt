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

project(StellaEngine)

#Versioning
set(Engine_Major_Version 0)
set(Engine_Minor_Version 0)
set(Engine_Patch 015)
set(DevRelease Y)                                                                                   #DevRelease? NOTE: After changing, rerun CMake to cache the change
set(UseQT N)                                                                                        #UseQt Modules?
set(Engine_Version ${Engine_Major_Version}.${Engine_Minor_Version}.${Engine_Patch})
if(DevRelease)
set(Engine_Version "${Engine_Version} DEV")
endif(DevRelease)

#Create Config
configure_file("${PROJECT_SOURCE_DIR}/EngineConfig.h.in" "${PROJECT_BINARY_DIR}/EngineConfig.h")
include_directories("${PROJECT_BINARY_DIR}")

#Include subdirs
add_subdirectory(headers)
add_subdirectory(processes)
add_subdirectory(launcher)
add_subdirectory(assets)

#Include OpenGL Resources
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
set(GLLibs ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})

#Include Qt Resources. Prefer standard OpenGL usage, but left as an option.
if(UseQT)
set(QtComp Core Widgets)                                                                            #Add to this list as requirements are updated
    if(WIN32)
    set(CMAKE_PREFIX_PATH C:/Qt/5.2.0/Src/qtbase/include)
    set(CMAKE_INCLUDE_PATH C:/Qt/5.2.0/Src/qtbase/include)
    else(WIN32)
    set(CMAKE_PREFIX_PATH ~/QtSDK/QtSources/5.2.0/Src/qtbase/include)
    set(CMAKE_INCLUDE_PATH ~/QtSDK/QtSources/5.2.0/Src/qtbase/include)
    endif(WIN32)
find_package(Qt5 REQUIRED COMPONENTS ${QtComp})
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
else(UseQT)
endif(UseQT)

#Create Execs
if(DevRelease)
add_executable(StellaEngine-Experimental main.cpp)
else(DevRelease)
add_executable(StellaEngine main.cpp)
endif(DevRelease)

#Link Launcher Libraries
add_executable(launcher/Launcher launcher/runLauncher.cpp)
if(UseQT)
qt5_use_modules(launcher/Launcher ${QtComp})
else(UseQT)
target_link_libraries(launcher/Launcher ${GLLibs})
endif(UseQT)
