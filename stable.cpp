#include <iostream>
#include "EngineConfig.h"
#include "processes/makeStarSys.h"
#include <string>

int main(int argc, char **argv) {
    std::cout << "Stella Engine: v." << Engine_Version;
    if(DevRelease == "Y") std::cout << " DEV";
    std::cout << std::endl;
    newStarSys("Sirius",15000);
    std::cout << "Destruction of Star System Commencing...";
    return 0;
}
