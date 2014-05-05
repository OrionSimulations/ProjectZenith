//#undef __STRICT_ANSI__
#include <iostream>
#include "EngineConfig.h"
#include "headers/celestial.h"
#include "headers/pangalactic.h"

int main(int argc, char **argv){
    printVersion();
    std::string blarg;
    float Loc[] = {0.,0.f,0.f};

    //Create Systems
    StarSystem Sirius(Loc);
    StarSystem ACentauri(Loc);
    Sirius.addCelestial(Star("Sirius A",9960));
    Sirius.addCelestial(Star("Sirius B",25200));
    Sirius.addCelestial(Terrestrial(Terrestrial::Terran,"Sirius I"));
    Sirius.addCelestial(Jovian(Jovian::Hydrogen,"Sirius II"));
    Sirius.updateSystem();
    ACentauri.addCelestial(Star("ACentauri A",5790));
    ACentauri.addCelestial(Star("ACentauri B",5260));
    ACentauri.addCelestial(Terrestrial(Terrestrial::Terran,"Alpha Centauri B b"));
    ACentauri.updateSystem();
    
    //View System Objects
    Sirius.viewSystem();
    ACentauri.viewSystem();
    std::cin >> blarg;
    return 0;
}
