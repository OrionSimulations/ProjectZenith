#ifndef CELESTIAL_H
#define CELESTIAL_H

#include <vector>
#include <list>
#include <set>
#include <string>
#include <sstream>

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

class Terrestrial : public SystemObject
{
private:
    int type;
    std::string name;
    const std::string primClass = "Terrestrial";
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
    Terrestrial(int thisType,std::string thisName) : type(thisType),name(thisName){std::cout << "Creating planet " << name << std::endl;}
    ~Terrestrial(){std::cout << "Destroying planet " << name << std::endl;}
    Terrestrial(const Terrestrial &source){
        type = source.type;
        name = source.name;
    }
    Terrestrial& operator= (const Terrestrial &source){
        if(this == &source) return *this;
        type = source.type;
        name = source.name;
        return *this;
    }
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
    }
};

class Jovian : public SystemObject
{
private:
    int type;
    std::string name;
    const std::string primClass = "Jovian";
public:
    enum Composite{
        Helium=1,
        Hydrogen,
        Nitrogen,
        Oxygen,
        Chlorine
    };
    Jovian(int thisType) : type(thisType),name("default"){std::cout << "Creating default Jovian" << std::endl;}
    Jovian(int thisType,std::string thisName) : type(thisType),name(thisName){std::cout << "Creating Jovian " << name << std::endl;}
    ~Jovian(){std::cout << "Destroying Jovian " << name << std::endl;}
    Jovian(const Jovian &source){
        type = source.type;
        name = source.name;
    }
    Jovian& operator= (const Jovian &source){
        if(this == &source) return *this;
        type = source.type;
        name = source.name;
        return *this;
    }
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
    std::string name;
    const std::string primClass = "Asteroid";
public:
    enum Composite{
        Metallic=1,
        Ice,
        Rock
    };
    Asteroid(int thisType) : type(thisType){}
    ~Asteroid(){}
    Asteroid(const Asteroid &source){
        type = source.type;
        name = source.name;
    }
    Asteroid& operator= (const Asteroid &source){
        if(this == &source) return *this;
        type = source.type;
        name = source.name;
        return *this;
     }
};

class AstBelt : public SystemObject
{
private:
    std::string name;
    const std::string primClass = "Asteroid Belt";
    std::vector<Asteroid> AstList;
public:
    AstBelt(std::vector<Asteroid> InitList) : AstList(InitList){}
    ~AstBelt(){}
    AstBelt(const AstBelt &source){
        name = source.name;
    }
    AstBelt& operator= (const AstBelt &source){
        if(this == &source) return *this;
        name = source.name;
        return *this;
     }
    void addAsteroid(Asteroid newAst){AstList.push_back(newAst);}
};

class Star : public SystemObject
{
private:
    int temp;
    char type;
    char setType(int temp)
    {
        if(temp >= 33000) return 'O';
        else if(temp >= 10000) return 'B';
        else if(temp >= 7500) return 'A';
        else if(temp >= 6000) return 'F';
        else if(temp >= 5200) return 'G';
        else if(temp >= 3700) return 'K';
        else if(temp >= 2000) return 'M';
        else return 0;
    }
    std::string name;
    std::string primClass = "Star";
public:
    Star(std::string newName, int startTemp) : name(newName),temp(startTemp),type(setType(startTemp)){std::cout << "Creating star " << newName << "..." << std::endl;}      //Replace with logging utility
    ~Star(){std::cout << "Destroying star " << this->getName() << "..." << std::endl;}
    Star(const Star &source){
        temp = source.temp;
        type = source.type;
        name = source.name;
    }
    Star& operator= (const Star &source){
        if(this == &source) return *this;
        temp = source.temp;
        type = source.type;
        name = source.name;
        return *this;
     }
    std::string getName(){return name;}
    std::string getClass(){return primClass;}
    std::string getSubClass(){std::stringstream ss; std::string s; ss << type; ss >> s; return s;}
};

class StarSystem
{
private:
    float* Location;
    std::list<Star> StarList;
    std::list<Terrestrial> Planetoids;
    std::list<Jovian> Jovians;
    std::list<AstBelt> AsteroidBelts;
    std::list<Asteroid> RogueAsteroids;
    std::list<SystemObject*> SystemObjectList;
public:
    StarSystem(float Vector3[3]) : Location(Vector3){}
    ~StarSystem(){}
    void setCenter(float Center[3]){Location = Center;}
    std::list<Terrestrial> getPlanetoids(){return Planetoids;}
    std::list<Jovian> getJovians(){return Jovians;}
    std::list<AstBelt> getAstBelts(){return AsteroidBelts;}
    std::list<Asteroid> getAsteroids(){return RogueAsteroids;}

    void addCelestial(Star StarObj){
        std::cout << "Adding Star " << StarObj.getName() << " to system..." << std::endl;
        StarList.push_back(StarObj);
    }

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
        std::cout << "Updating system..." << std::endl;                                                             //Replace with logging utility
        SystemObjectList.clear();
        for(Star &thisStar : StarList) SystemObjectList.push_back(&thisStar);
        for(Terrestrial &thisPlanet : Planetoids) SystemObjectList.push_back(&thisPlanet);
        for(Jovian &thisPlanet : Jovians) SystemObjectList.push_back(&thisPlanet);
        for(AstBelt &thisBelt : AsteroidBelts) SystemObjectList.push_back(&thisBelt);
        for(Asteroid &thisAst : RogueAsteroids) SystemObjectList.push_back(&thisAst);
    }

    void viewSystem(){
        std::cout << "Stellar bodies: ";
        if(SystemObjectList.size() == 0) std::cout << "None.";
        else{
            short NameBuffer = 0, ClassBuffer = 0, SubClassBuffer = 0;
            for(SystemObject *thisObject : SystemObjectList){
                if(thisObject->getName().length() > NameBuffer) NameBuffer = thisObject->getName().length();
                if(thisObject->getClass().length() > ClassBuffer) ClassBuffer = thisObject->getClass().length();
                if(thisObject->getSubClass().length() > SubClassBuffer) SubClassBuffer = thisObject->getSubClass().length();
            }
            std::cout << SystemObjectList.size() << std::endl;
            for(int i=0;i<NameBuffer+ClassBuffer+SubClassBuffer+13;i++) std::cout << "=";
            std::cout << std::endl;
            for(SystemObject *thisObject : SystemObjectList){
                std::cout << "| ";
                std::cout << thisObject->getName();
                for(int i=thisObject->getName().length();i<=NameBuffer;i++) std::cout << " ";
                std::cout << " | ";
                std::cout << thisObject->getClass();
                for(int i=thisObject->getClass().length();i<=ClassBuffer;i++) std::cout << " ";
                std::cout << " | ";
                std::cout << thisObject->getSubClass();
                for(int i=thisObject->getSubClass().length();i<=SubClassBuffer;i++) std::cout << " ";
                std::cout << " |";
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
};

#endif
