cmake_minimum_required(VERSION 2.8.9)
cmake_policy(SET CMP0020 NEW)
if(WIN32)
set(WIN_LIB_DIR "C:/ProjectLibs")
link_directories(${WIN_LIB_DIR}/lib)
endif(WIN32)
set(GCC_COMP_FLAGS "-static-libgcc -static-libstdc++ -std=gnu++0x -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMP_FLAGS}")
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
find_program(CMAKE_CXX_COMPILER g++)
find_program(CMAKE_C_COMPILER gcc)

project(Stella-Launcher)

#Include OpenGL Resources
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
set(GLLibs ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
set(DevRelease ${DevRelease} CACHE BOOL "Set to Y if Development Build; N otherwise" FORCE)

#Launcher Version System
set(UseQT ${UseQt} CACHE BOOL "Specifies whether the Qt Libraries are used" FORCE)

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
endif(UseQT)

#Include Stella Library
find_package(Stella REQUIRED)
set(StellaLib ${STELLA_LIBRARIES})

#Add Debugging information (DevReleases)
if(DevRelease)
set(CMAKE_BUILD_TYPE "Debug")
else(DevRelease)
set(CMAKE_BUILD_TYPE "Release")
endif(DevRelease)

#Link Launcher Libraries
add_executable(Stella-Launcher runLauncher.cpp)
if(UseQT)
qt5_use_modules(Stella-Launcher ${QtComp})
else(UseQT)
target_link_libraries(Stella-Launcher ${GLLibs} ${StellaLib} ${CMAKE_DL_LIBS})
endif(UseQT)

#Install Executable
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
set(CMAKE_INSTALL_PREFIX ~/.zenith CACHE PATH "Standard Zenith Installation Directory" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
install(TARGETS Stella-Launcher RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory \${CMAKE_INSTALL_PREFIX}/modules)")
install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory \${CMAKE_INSTALL_PREFIX}/assets)")