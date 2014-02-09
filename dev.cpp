#undef __STRICT_ANSI__
#include <iostream>
#include "EngineConfig.h"
#include "headers/celestial.h"
#include "headers/pangalactic.h"
#include <string>

int main(int argc, char **argv){
    std::string version = "Stella Engine: v.";
    version.append(Engine_Version);
    //std::cout << "Stella Engine: v." << Engine_Version;
    if(DevRelease == "Y") version.append(" DEV");
    std::cout << version << std::endl;
    Star Sirius("Sirius",15000);
    //Sirius.addCelestial(Terrestrial(Terrestrial::Terran,"Sirius I"));
    Sirius.addCelestial(Jovian(Jovian::Chlorine,"Sirius II"));
    Sirius.updateSystem();
    std::cout << "Stellar bodies: " << std::endl;
    if(Sirius.getAllBodies().size() == 0) std::cout << "None.";
    else{
        for(SystemObject &thisObject : Sirius.getJovians()) std::cout << thisObject.getName() << '\t' << thisObject.getClass() << '\t' << thisObject.getSubClass() << std::endl;
    }
    std::cout << std::endl;
    return 0;
}
