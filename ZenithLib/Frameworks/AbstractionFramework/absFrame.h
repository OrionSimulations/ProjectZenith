#ifndef ABS_FRAME
#define ABS_FRAME

class AbstractionFramework{

public:
	AbstractionFramework(){
		std::cout << "Initializing Abstraction Framework..." << std::endl;
	}
	~AbstractionFramework(){
		std::cout << "Destroying Abstraction Framework..." << std::endl;
	}
};

#endif