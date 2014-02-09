#ifndef PANGALACTIC_H
#define PANGALACTIC_H

#include <vector>

class GalaxyCenter
{
private:
    double radius;
public:
    GalaxyCenter(double thisRadius) : radius(thisRadius){}
    GalaxyCenter() : radius(1){}
    ~GalaxyCenter(){}
};

class StarCluster
{
private:
    int numStars;
public:
    StarCluster(int starCount) : numStars(starCount){}
    ~StarCluster(){}
};

class SpiralArm
{
private:
    double length, width;
    std::vector<StarCluster> LocalClusters;
public:
    SpiralArm(double thisLength, double thisWidth, int numClusters) : length(thisLength),width(thisWidth){}
    SpiralArm(std::vector<StarCluster> Clusters) : LocalClusters(Clusters){}
    ~SpiralArm(){}
};

class Galaxy
{
private:
    enum Type{
        Barred=1,
        Spiral,
        Elliptical,
        Cluster,
        Peculiar
    };
    int type;
    double age;
    GalaxyCenter Core;
    std::vector<SpiralArm> Arms;
public:
    Galaxy(double currentAge, GalaxyCenter thisCore, std::vector<SpiralArm> armList) : age(currentAge),Core(thisCore),Arms(armList){}
    ~Galaxy(){}
};

class Sector
{
private:
    std::vector<Galaxy> Galaxies;
public:
    Sector(std::vector<Galaxy> galaxyList) : Galaxies(galaxyList){}
    ~Sector();
};

#endif
