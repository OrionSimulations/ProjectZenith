#ifndef MAKESTARSYS_H
#define MAKESTARSYS_H

#include "../headers/celestial.h"
#include "../headers/pangalactic.h"
#include <iostream>
#include <string>

using namespace::std;

void addTerToStar(Star modStar,Terrestrial newPlanet){
    cout << "Adding Terrestrial " << newPlanet.getName() << "..." << endl;
}

void addJovToStar(Star modStar,Jovian newPlanet){
    cout << "Adding Jovian " << newPlanet.getName() << "..." << endl;
}

#endif
