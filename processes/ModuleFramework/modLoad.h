#ifndef MODLOAD
#define MODLOAD

#include <list>
#include <string>
#include <iostream>
#include <dirent.h>
#include <iterator>
#include <omp.h>
// #include <glog/logging.h>

#if WIN_BUILD
#include <windows.h>
#else
#include <dlfcn.h>
#endif

//Module Definitions

struct buildEnv{
	static std::string ModDir;
	static std::string BuildDir;
	#if WIN_BUILD
	static const char dirDelim = '\\';
	#else
	static const char dirDelim = '/';
	#endif
};

struct Module{
	static int nextModID;
	int id;
	const char* name;
	void *mod_lib;
	typedef void (*func_t)(void);
	func_t lib_init;
	func_t lib_update;

	Module(const char* newName, void* modLibrary, func_t modInit, func_t modUpdate): id(nextModID), name(newName), mod_lib(modLibrary), lib_init(modInit), lib_update(modUpdate){(*lib_init)(); nextModID++;}
	~Module(){
		std::cout << "Unloading " << this->name << "..." << std::endl;
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
	void initModSys(std::string rootDir);
	void loadModule(const char* ModName);
	void unloadModule(Module toUnload);
	void listModules();
	void updateModList();
	void callModule(Module &toCall, const char* functionName);
	void callUpdate(Module &toUpdate);
	void autoLoadModules();
	void autoModDir(const char* ModName);

public:
	ModuleFramework(std::string rootDir){
		std::cout << "Creating Framework..." << std::endl;
		initModSys(rootDir);
//OpenMP: Run all module update functions
#pragma omp parallel num_threads(ModList.size())
		{
			int ID = omp_get_thread_num();
			auto it = std::next(ModList.begin(),ID);
			callUpdate(**it);
		}
	}
	~ModuleFramework(){
		std::cout << "Destroying Framework..." << std::endl;
		for(Module *ref : ModList){
			std::cout << " - ";
			delete ref;
		}
		updateModList();
	}
};

#endif