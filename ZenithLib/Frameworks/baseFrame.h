#ifndef BASE_FRAME
#define BASE_FRAME

#include <list>
#include <string>
#include <iostream>

#if WIN_BUILD
#include <windows.h>
#else
#include <dlfcn.h>
#endif

template <typename T_Container>
class BaseFramework{

	std::list<T_Container*> InstList;
	void listLibs();
	void updateLibList();
	void callLibProc(T_Container &internalRef, const char* sysCall);

public:
	BaseFramework(const char* contentLocation){
		std::cout << "Creating Framework..." << std::endl;
		const char* reqFunc[] = {(char*)"initialize",(char*)"update"};
		ContentLoader<T_Container> CTLoader(contentLocation,reqFunc);
		InstList = CTLoader.exportContentList();
	}
	~BaseFramework(){
		std::cout << "Destroying Framework..." << std::endl;

		for(T_Container *ref : InstList){
			std::cout "-";
			delete ref;
		}
		updateLibList();
	}
};

struct LibInstance{
	const char* name;
	void* lib_ref;
	typedef void (*func_t)(void);
	func_t lib_init;

	LibInstance();
	~LibInstance(){
		std::cout << "Unloading Module " << this->name << "..." << std::endl;
#if WIN_BUILD
		FreeLibrary(this->lib_ref);
#else
		if(dlclose(this->lib_ref)) std::cout << dlerror() << std::endl;
#endif
		this->lib_ref = NULL;
	}

};

#endif