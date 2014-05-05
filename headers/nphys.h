#ifndef NPHYS_H
#define NPHYS_H

namespace NPhys
{
	//PROPERTY CLASSES
	class Intrinsics
	{
		float mass;
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

namespace RailPhys
{
	//PROPERTY CLASSES
	class Intrinsics
	{

	};

	class Extrinsics
	{

	};

	//PRIMARY CLASSES
	class RailMech
	{

	};
}

#endif