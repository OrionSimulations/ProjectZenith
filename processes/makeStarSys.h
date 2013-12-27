#ifndef MAKESTARSYS_H
#define MAKESTARSYS_H

#include "../headers/celestial.h"
#include "../headers/pangalactic.h"
#include <iostream>
#include <string>

using namespace::std;

void newStarSys(string starName,int temp){
    cout << "Creating " << starName << "..." << endl;
    Star newStar = Star(starName,temp);
    cout << "Star " << starName << " has been created successfully." << endl;
    cout << "Star added to universe." << endl;
}

void newStarSys(Star newStar){
    cout << "Creating " << newStar.getStarName() << "..." << endl;
    cout << "Star added to universe." << endl;
}

void addTerToStar(Star modStar,Terrestrial newPlanet){
    cout << "Adding Terrestrial " << newPlanet.getName() << "..." << endl;
}

#endif
