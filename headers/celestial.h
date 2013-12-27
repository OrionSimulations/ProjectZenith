#ifndef CELESTIAL_H
#define CELESTIAL_H

#include <vector>
#include <string>

class Terrestrial
{
private:
  enum Class{
    Terran=1,
    Oceanic,
    Desert,
    Tundra,
    Barren
  };
  int type;
  std::string name;
public:
  Terrestrial(int thisType) : type(thisType){}
  ~Terrestrial(){}
  std::string getName(){return name;}
};

class Asteroid
{
private:
  enum Class{
    Metallic=1,
    Ice,
    Rock
  };
  int type;
public:
  Asteroid(int thisType) : type(thisType){}
  ~Asteroid(){}
};


class AstBelt
{
private:
  int numAsteroids;
  std::vector<Asteroid> AstList;
public:
  AstBelt(int AstCount) : numAsteroids(AstCount){}
  ~AstBelt(){}
  void addAsteroid(Asteroid newAst);
};

void AstBelt::addAsteroid(Asteroid newAst)
{
  AstList.push_back(newAst);
}

class Jovian
{
private:
  enum Composite{
    Helium=1,
    Hydrogen,
    Nitrogen,
    Oxygen,
    Chlorine
  };
  int type;
public:
  Jovian(int thisType) : type(thisType){}
  ~Jovian(){}
};

class OrbitalCenter
{
private:
  std::vector<int> Location;
public:
  OrbitalCenter(std::vector<int> Vector3) : Location(Vector3){}
  ~OrbitalCenter(){}
  void setCenter(std::vector<int> Center){Location = Center;}
};

class Star
{
private:
  enum Class{O=1, B, A, F, G, K, M};
  int temp;
  int type;
  bool isSingular;
  int setType(int temp);
  void setCompanions(std::vector<Star> Companions){CompanionStars = Companions;}
  std::string name;
  std::vector<Star> CompanionStars;
  std::vector<Terrestrial> Planetoids;
  std::vector<Jovian> Jovians;
  std::vector<AstBelt> AsteroidBelts;
  std::vector<Asteroid> RogueAsteroids;
public:
  Star(std::string newName, int startTemp, std::vector<Star> Companions) : name(newName),temp(startTemp),type(setType(startTemp)),CompanionStars(Companions){}
  Star(std::string newName, int startTemp) : name(newName),temp(startTemp),type(setType(startTemp)){}
  ~Star(){}
  std::string getStarName(){return name;}
  void addCelestial(Terrestrial Planetoid){Planetoids.push_back(Planetoid);}
  void addCelestial(Jovian LargePlanetoid){Jovians.push_back(LargePlanetoid);}
  void addCelestial(AstBelt Belt){AsteroidBelts.push_back(Belt);}
  void addCelestial(Asteroid thisAsteroid){RogueAsteroids.push_back(thisAsteroid);}
};

int Star::setType(int temp)
{
  if(temp >= 33000) type = O;
  else if(temp >= 10000) type = B;
  else if(temp >= 7500) type = A;
  else if(temp >= 6000) type = F;
  else if(temp >= 5200) type = G;
  else if(temp >= 3700) type = K;
  else if(temp >= 2000) type = M;
  else type = 0;
}

#endif
