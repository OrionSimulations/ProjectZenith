#ifndef OBJFRAME
#define OBJFRAME

#include <vector>
#include <list>
#include <set>
#include <string>
#include <sstream>
// #include <glog/logging.h>

class ObjectFramework{
private:
    void initObjSys();
    void loadObject();
    void unloadObject();
    void viewObjects();

public:
    ObjectFramework(){}
    ~ObjectFramework(){}
};

#endif