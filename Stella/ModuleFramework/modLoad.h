#ifndef MODLOAD
#define MODLOAD

#include <list>
#include <string>
#include <iostream>
#include <iterator>
#include <omp.h>
// #include <glog/logging.h>

#include "../contentLoad.h"

#if WIN_BUILD
#include <windows.h>
#else
#include <dlfcn.h>
#endif

//Module Definitions

struct Module{
	static int nextModID;
	int id;
	const char* name;
	void *mod_lib;
	typedef void (*func_t)(void);
	func_t lib_init;
	func_t lib_update;

	Module(const char* newName, void* modLibrary, std::list<func_t> funcList): id(nextModID), name(newName), mod_lib(modLibrary), lib_init(*(funcList.begin())), lib_update(*(++funcList.begin())){
		std::cout << "[" << name << "]: Initializing" << std::endl;
		(*lib_init)();
		nextModID++;
	}
	~Module(){
		std::cout << "Unloading Module " << this->name << "..." << std::endl;
#if WIN_BUILD
		FreeLibrary(this->mod_lib);
#else
		if(dlclose(this->mod_lib)) std::cout << dlerror() << std::endl;
#endif
		this->mod_lib = NULL;
	}
};

class ModuleFramework{
	std::list<Module*> ModList;
	//Module Loading Mechanism Declarations
	void listModules();
	void updateModList();
	void callModule(Module &toCall, const char* functionName);
	void callUpdate(Module &toUpdate);

public:
	ModuleFramework(){
		std::cout << "Creating Module Framework..." << std::endl;
		const char* reqFunc[] = {(char*)"initialize",(char*)"update"};
		std::list<const char*> requiredFuncs;//(reqFunc,reqFunc+1);
		requiredFuncs.push_back(*reqFunc);
		requiredFuncs.push_back(reqFunc[1]);
		ContentLoader<Module> modLoader(buildEnv::ModDir.c_str(),requiredFuncs);
		ModList = modLoader.exportContentList();
//OpenMP: Run all module update functions
		if(ModList.size() > 0){
#pragma omp parallel num_threads(ModList.size())
			{
				int ID = omp_get_thread_num();
				auto it = std::next(ModList.begin(),ID);
				callUpdate(**it);
				#pragma omp barrier
			}
		}
	}
	~ModuleFramework(){
		std::cout << "Destroying Module Framework..." << std::endl;
		for(Module *ref : ModList){
			std::cout << " - ";
			delete ref;
		}
		updateModList();
	}
};

#endif