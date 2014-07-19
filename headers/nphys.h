#ifndef NPHYS_H
#define NPHYS_H

// N-Body Simulation Classes
namespace NPhys
{
	//PROPERTY CLASSES
	class ObjectProperties
	{
		//Celestial Body Properties
		float mass;
		float SRP;

		//Orbital Properties
		float velocity[];
		float acceleration[];
		float Perigee;
		float Apogee;
		float MAE;
		float 

	};

	class Intrinsics
	{
		float mass;
		float SRP;
	};

	class Extrinsics
	{
		//Extrinsic values
		float velocity[];
		float acceleration[];
		float Perigee[];
		float Apogee[];
		float MAE;
	};

	//PRIMARY CLASSES
	class OrbitMech
	{
		
	};

	class GravSource
	{

	};
}

// Newtonian (Rail) Simulation Classes
namespace RailPhys
{
	//PROPERTY CLASSES
	class Intrinsics
	{
		float mass;
	};

	class Extrinsics
	{

	};

	//PRIMARY CLASSES
	class RailMech
	{

	};
}

namespace Conics
{
	//CONIC SECTION CLASSES
}

#endif