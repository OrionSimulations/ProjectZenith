#include "modLoad.h"

//Static Member Declarations

int Module::nextModID = 0;

//Module Framework Method Prototypes

void ModuleFramework::listModules(){
	for(Module *thismod : ModList){
		if(thismod->mod_lib){
			std::cout << Section::stringSec(1,NULL,"Module: ") << thismod->name << std::endl;
			std::cout << Section::stringSec(2,Section::Increase) << std::endl;
			std::cout << Section::stringSec(2,Section::Item,"ModID: ") << thismod->id << std::endl;
			std::cout << Section::stringSec(2,Section::Decrease) << std::endl;
		}
	}
}

//DO NOT USE OUTSIDE FRAMEWORK DESTRUCTOR!!!
void ModuleFramework::updateModList(){
	ModList.remove_if([](Module const *ref){return !ref->mod_lib;});
	if(!ModList.empty()) std::cout << ModList.size() << " modules still loaded into memory." << std::endl;
}

void ModuleFramework::callModule(Module &toCall, const char* functionName){
#if WIN_BUILD

#else
	char* errorLog;
	//Clear the loading error buffer, so we can check if an actual error occurs
	dlerror();
	if(!toCall.mod_lib){
		std::cout << "Module Library corrupted! Aborting call..." << std::endl;
		return;
	}
	void* lib = toCall.mod_lib;
	typedef void (*func_t)(void);
	func_t call = (func_t) dlsym(lib,functionName);
	(*call)();
	errorLog = dlerror();
	if(errorLog != "") std::cout << dlerror() << std::endl;
	return;
#endif
	std::cout << "Module is not available. Has it been loaded?" << std::endl;
}

void ModuleFramework::callUpdate(Module &toUpdate){
#if WIN_BUILD

#else
	if(!toUpdate.mod_lib){
		std::cout << "Module Library corrupted! Aborting call..." << std::endl;
		return;
	}
	(*toUpdate.lib_update)();
#endif
}