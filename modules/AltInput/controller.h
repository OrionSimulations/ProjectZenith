#ifndef CONTROLLER_H
#define CONTROLLER_H

/*
 *	Encapsulation of controller input for Engine
 */

namespace controllerInput
{
	typedef struct Controller{
		int ID;
		char* name;
		float* axes;
		unsigned char* keys;
		int axisCount;
		int keyCount;
	} Controller;

	class ControllerCommand{

	};

	class ControllerProcessing{

	};
}

#endif CONTROLLER_H