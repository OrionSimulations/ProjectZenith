#ifndef PANGALACTIC_H
#define PANGALACTIC_H

#include <vector>

class GalaxyCenter
{
private:
  double radius;
public:
  GalaxyCenter(double thisRadius);
  GalaxyCenter();
  ~GalaxyCenter(){}
};

GalaxyCenter::GalaxyCenter(double thisRadius)
{
  radius = thisRadius;
}

GalaxyCenter::GalaxyCenter()
{
  radius = 1;
}

class StarCluster
{
private:
  int numStars;
public:
  StarCluster(int starCount);
  ~StarCluster(){}
};

class SpiralArm
{
private:
  double length, width;
  std::vector<StarCluster> LocalClusters;
public:
  SpiralArm(double length, double width);
  ~SpiralArm(){}
};

class Galaxy
{
private:
  double age;
  GalaxyCenter Core;
  std::vector<SpiralArm> Arms;
public:
  Galaxy(double currentAge, GalaxyCenter thisCore, std::vector<SpiralArm> armList);
  ~Galaxy(){}
};

Galaxy::Galaxy(double currentAge, GalaxyCenter thisCore, std::vector<SpiralArm> armList)
{
  age = currentAge;
  Core = thisCore;
  Arms = armList;
}

class Sector
{
private:
  int numGalaxies;
  std::vector<Galaxy> Galaxies;
public:
  Sector(int galaxyCount, std::vector<Galaxy> galaxyList);
  ~Sector();
};

#endif
