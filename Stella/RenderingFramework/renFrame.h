#ifndef REN_FRAME
#define REN_FRAME

class RenderingFramework{

public:
	RenderingFramework(){
		std::cout << "Initializing Rendering Framework..." << std::endl;
	}
	~RenderingFramework(){
		std::cout << "Destroying Rendering Framework..." << std::endl;
	}
};

#endif