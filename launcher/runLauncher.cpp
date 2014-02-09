#include "launchbase.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>

/*//Qt module launcher. Retained as a secondary option.
int main(int argc, char **argv)
{
    QApplication launch(argc,argv);
    launchBase launcher;
    launcher.show();
    return launch.exec();
}
//*/

double lastFrame = 0;

static void error_callback(int error, const char* desc){
}

static void key_callback(GLFWwindow* caller, int key, int scanCode, int action, int mods){
    switch(mods){
        case GLFW_MOD_SHIFT:
            break;
        case GLFW_MOD_CONTROL:
            break;
        case GLFW_MOD_ALT:
            break;
        case GLFW_MOD_SUPER:
            break;
        default:
            if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(caller,GL_TRUE);
            break;
    }
}

static void mouse_callback(GLFWwindow* caller,double,double){
}

static void mouse_click_callback(GLFWwindow* caller, int button, int action, int mods){
    switch(mods){
        case GLFW_MOD_SHIFT:
            break;
        case GLFW_MOD_CONTROL:
            break;
        case GLFW_MOD_ALT:
            break;
        case GLFW_MOD_SUPER:
            break;
        default:
        break;
    }
}

static void mouse_scroll_callback(GLFWwindow* caller, double deltaX, double deltaY){
}

int main(int argc, char **argv)
{
    if(!glfwInit()) return -1;
    GLFWwindow* launchMain = glfwCreateWindow(1024,768,"Launcher",glfwGetPrimaryMonitor(),NULL);
    if(!launchMain){
        glfwTerminate();
        return -1;
    }
    //Set GLFW Callback Functions
    glfwSetKeyCallback(launchMain,key_callback);
    glfwSetCursorPosCallback(launchMain,mouse_callback);
    glfwSetMouseButtonCallback(launchMain,mouse_click_callback);
    glfwSetScrollCallback(launchMain,mouse_scroll_callback);
    //END Set GLFW Callback Functions

    glfwMakeContextCurrent(launchMain);
    glfwSetTime(0);
    while(!glfwWindowShouldClose(launchMain)){
        glfwWaitEvents();
    }
    glfwDestroyWindow(launchMain);
    glfwTerminate();
    return 0;
}
