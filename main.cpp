#include <iostream>
#include "EngineConfig.h"
#include "headers/celestial.h"
#include "headers/pangalactic.h"
#include "processes/ModuleFramework/modLoad.h"
#include "processes/ObjectFramework/objFrame.h"
//include <glog/logging.h>

int main(int argc, char **argv){
    printVersion();

    //Load glog from build tree, preferably before the Module Framework is loaded
    //I'll get around to this eventually... -CTE Schmitty
    // FLAGS_log_dir = argv[0];
    // google::InitGoogleLogging(argv[0]);
    // LOG(INFO) << "Initializing Framework...";

    //Initialize Module Framework Object
    ModuleFramework *frame = new ModuleFramework(argv[0]);

    std::string blarg;
    float Loc[] = {0.f,0.f,0.f};

    //Create Systems for basic object framework testing.
    //This mechanism will be overhauled with CAP implementation
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
    //Again, will be overhauled with CAP implementation
    Sirius.viewSystem();
    ACentauri.viewSystem();

    std::cin >> blarg;

    //Destroy Module Framework Object
    delete frame;

    return 0;
}
