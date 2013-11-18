#ifndef MAKESTARSYS_H
#define MAKESTARSYS_H

#include "../headers/celestial.h"
#include "../headers/pangalactic.h"
#include <iostream>
#include <string>

using namespace::std;

void newStarSys(){
  string starName;
  int temp;
  string exit;
  cout << "Star name: ";
  cin >> starName;
  cout << "Star temperature: ";
  cin >> temp;
  cout << "Creating " + starName + "..." << endl;
  Star newStar = Star(starName,temp);
  cout << "Star " + starName + " has been created successfully." << endl;
}

#endif