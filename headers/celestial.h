#ifndef CELESTIAL_H
#define CELESTIAL_H

#include <vector>
#include <list>
#include <set>
#include <string>
#include <algorithm>

class SystemObject
{
private:
    std::string name;
    std::string primClass;
    std::string subClass;
public:
    SystemObject(){}
    ~SystemObject(){}
    virtual std::string getName(){return name;}
    virtual std::string getClass(){return primClass;}
    virtual std::string getSubClass(){return subClass;}
};

struct classComp {
    bool operator()(SystemObject A, SystemObject B){
        return(A.getName() < B.getName());
    }
};

class Terrestrial : public SystemObject
{
private:
    int type;
    std::string name;
public:
    enum Class{
        Terran=1,
        Oceanic,
        Desert,
        Tundra,
        Barren
    };
    Terrestrial() : type(Terrestrial::Terran),name("default"){std::cout << "Creating default Terran" << std::endl;}
    Terrestrial(int thisType) : type(thisType),name("default"){std::cout << "Creating default planet" << std::endl;}
    Terrestrial(int thisType,std::string thisName) : type(thisType),name(thisName){std::cout << "Creating planet " << this->getName() << std::endl;}
    ~Terrestrial(){std::cout << "Destroying planet " << this->getName() << std::endl;}
    std::string getName(){return name;}
    std::string getClass(){return "Terrestrial";}
    std::string getSubClass(){
        switch(type){
        case Terran: return "Terran";
        case Oceanic: return "Oceanic";
        case Desert: return "Desert";
        case Tundra: return "Tundra";
        case Barren: return "Barren";
        default: return "Unknown";
        }

        /*
        if(type == Terran) return "Terran";
        else if(type == Oceanic) return "Oceanic";
        else if(type == Desert) return "Desert";
        else if(type == Tundra) return "Tundra";
        else if(type == Barren) return "Barren";
        return "Unknown";
        */
    }
};

class Jovian : public SystemObject
{
private:
    int type;
    std::string name;
public:
    enum Composite{
        Helium=1,
        Hydrogen,
        Nitrogen,
        Oxygen,
        Chlorine
    };
    Jovian(int thisType) : type(thisType),name("default"){}
    Jovian(int thisType,std::string thisName) : type(thisType),name(thisName){}
    ~Jovian(){}
    std::string getName() {return name;}
    std::string getClass(){return "Jovian";}
    std::string getSubClass(){
        switch(type){
        case Helium: return "Helium";
        case Hydrogen: return  "Hydrogen";
        case Nitrogen: return "Nitrogen";
        case Oxygen: return "Oxygen";
        case Chlorine: return "Chlorine";
        default: return "Unknown";
        }
    }
};

class Asteroid : public SystemObject
{
private:
    int type;
public:
    enum Composite{
        Metallic=1,
        Ice,
        Rock
    };
    Asteroid(int thisType) : type(thisType){}
    ~Asteroid(){}
};

class AstBelt : public SystemObject
{
private:
    int numAsteroids;
    std::vector<Asteroid> AstList;
public:
    AstBelt(int AstCount) : numAsteroids(AstCount){}
    ~AstBelt(){}
    void addAsteroid(Asteroid newAst){AstList.push_back(newAst);}
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
    std::list<Terrestrial> Planetoids;
    std::list<Jovian> Jovians;
    std::list<AstBelt> AsteroidBelts;
    std::list<Asteroid> RogueAsteroids;
    std::list<SystemObject> SystemObjectTemp;
    std::set<SystemObject,classComp> SystemObjects;
public:
    Star(std::string newName, int startTemp, std::vector<Star> Companions) : name(newName),temp(startTemp),type(setType(startTemp)),CompanionStars(Companions){std::cout << "Creating star " << newName << "..." << std::endl;}      //Replace with logging utility
    Star(std::string newName, int startTemp) : name(newName),temp(startTemp),type(setType(startTemp)){std::cout << "Creating star " << newName << "..." << std::endl;}
    ~Star(){std::cout << "Destroying star " << this->getStarName() << "..." << std::endl;}
    std::string getStarName(){return name;}
    std::list<Terrestrial> getPlanetoids(){return Planetoids;}
    std::list<Jovian> getJovians(){return Jovians;}
    std::list<AstBelt> getAstBelts(){return AsteroidBelts;}
    std::list<Asteroid> getAsteroids(){return RogueAsteroids;}
    std::set<SystemObject,classComp> getAllBodies(){return SystemObjects;}

    void addCelestial(Terrestrial Planetoid){
        std::cout << "Adding Planetoid " << Planetoid.getName() << " to system..." << std::endl;                    //Replace with logging utility
        Planetoids.push_back(Planetoid);
    }
    void addCelestial(Jovian LargePlanetoid){
        std::cout << "Adding Jovian " << LargePlanetoid.getName() << " to system..." << std::endl;                  //Replace with logging utility
        Jovians.push_back(LargePlanetoid);
    }
    void addCelestial(AstBelt Belt){
        std::cout << "Adding Asteroid Belt to system..." << std::endl;                                              //Replace with logging utility
        AsteroidBelts.push_back(Belt);
    }
    void addCelestial(Asteroid thisAsteroid){
        std::cout << "Adding Asteroid to system..." << std::endl;                                                   //Replace with logging utility
        RogueAsteroids.push_back(thisAsteroid);
    }
    void updateSystem(){
        for(Terrestrial &thisP : Planetoids) SystemObjectTemp.push_back(thisP);
        for(Jovian &thisJ : Jovians) SystemObjectTemp.push_back(thisJ);
        for(Asteroid &thisA : RogueAsteroids) SystemObjectTemp.push_back(thisA);
        for(AstBelt &thisABelt : AsteroidBelts) SystemObjectTemp.push_back(thisABelt);
        //for(SystemObject &thisObj : SystemObjectTemp) SystemObjects.insert(thisObj);
        //std::cout << "Objects in SystemObjects set: " << std::endl;
        //for(SystemObject &thisObj : SystemObjects) std::cout << thisObj.getName() << std::endl;
        //SystemObjects.insert(SystemObjectTemp.begin(),SystemObjectTemp.end());
        //SystemObjectTemp.merge(&Planetoids);
        //SystemObjectTemp.merge(&Jovians);
        //SystemObjectTemp.merge(&AsteroidBelts);
        //SystemObjectTemp.merge(&RogueAsteroids);
        //std::copy(SystemObjectTemp.begin(),SystemObjectTemp.end(),SystemObjects.begin());
    }
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
