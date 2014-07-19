#include "modLoad.h"

//Static Member Declarations

/*
 *	Struct static members:
 *	struct buildEnv
 *		ModDir
 *		BuildDir
 *	struct Module
 *		nextModID
 */

int Module::nextModID = 0;
std::string buildEnv::ModDir;
std::string buildEnv::BuildDir;
const std::string S1Prefix = " - ";
const std::string SectionScope = "   \\ ";
const std::string SectionItem = "   | ";
const std::string SectionDecrease = "   / ";

std::string stringMod(std::string prefix, std::string BaseString){
	return prefix+BaseString;
}

//Module Loading Mechanisms Prototypes

void ModuleFramework::initModSys(std::string rootDir){
	ModList.empty();
	buildEnv::BuildDir = rootDir;
	buildEnv::ModDir = rootDir.substr(0,rootDir.rfind(buildEnv::dirDelim)+1)+"modules"+buildEnv::dirDelim;
	autoLoadModules();
	listModules();

}

/* No longer necessary (TO BE DELETED)
void ModuleFramework::loadModule(const char* ModName){
	std::string ModLoc = buildEnv::ModDir + ModName;
	DIR *progDir = opendir(ModLoc.c_str());
	struct dirent *drnt;
	if(progDir){
		std::string dirLoc;
		while(drnt = readdir(progDir)){
			dirLoc = std::string(drnt->d_name);
			if(dirLoc.find(".so") != std::string::npos || dirLoc.find(".dll") != std::string::npos){
				ModLoc += buildEnv::dirDelim + dirLoc;
				break;
			}
		}
		closedir(progDir);
	}

	std::cout << "Loading " << ModLoc << " ..." << std::endl;
//Fucking NT Kernel...
#if WIN_BUILD
	HMODULE mod_lib = LoadLibrary(ModLoc.c_str());
	if(!mod_lib){
		std::cout << "Module failed to load properly." << std::endl;
		return;
	}
#else
	void *mod_lib = dlopen(ModLoc.c_str(),RTLD_NOW);
	if(!mod_lib){
		std::cout << dlerror() << std::endl;
		return;
	}
#endif
	if(mod_lib){
		ModList.push_front(new Module(ModName,mod_lib));
	}
}
*/

void ModuleFramework::unloadModule(Module toUnload){
#if WIN_BUILD
	FreeLibrary(toUnload.mod_lib);
#else
	if(dlclose(toUnload.mod_lib)) std::cout << dlerror() << std::endl;
#endif
	toUnload.mod_lib = NULL;
	updateModList();
}

void ModuleFramework::listModules(){
	for(Module *thismod : ModList){
		if(thismod->mod_lib){
			std::cout << stringMod(S1Prefix,"Module: ") << thismod->name << std::endl;
			std::cout << SectionScope << std::endl;
			std::cout << stringMod(SectionItem,"ModID: ") << thismod->id << std::endl;
			std::cout << SectionDecrease << std::endl;
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

//Module Framework Automatic Mechanisms

void ModuleFramework::autoLoadModules(){
	DIR *progDir = opendir(buildEnv::ModDir.c_str());														//Open Program Modules Directory
	struct dirent *dirRoot;																					//Allocate Directory Struct
	char* ModName;																							//Allocate Module Name and Location
	if(progDir){
		dirRoot = readdir(progDir);																			//Skip Parent Directory
		dirRoot = readdir(progDir);																			//Skip Current Directory
		char* mod = NULL;
		while(dirRoot = readdir(progDir)){																	//Read Next Directory
			if(dirRoot->d_type & DT_DIR){
				mod = dirRoot->d_name + '\0';
				autoModDir(mod);
			}
		}
		closedir(progDir);
	}
}

void ModuleFramework::autoModDir(const char* ModName){
	DIR *modDir = NULL;																						//Allocate Module Directory
	struct dirent *drnt;																					//Allocate Module Directory Struct
	std::string thisMod = buildEnv::ModDir + std::string(ModName);
	std::string file;																						//Allocate library path

	modDir = opendir(thisMod.c_str());																		//Open Module Directory
	while(drnt = readdir(modDir)){
		file = std::string(drnt->d_name);
		if(file.find(".so") != std::string::npos || file.find(".dll") != std::string::npos){
			thisMod += buildEnv::dirDelim + file;
			break;
		}
	}
	closedir(modDir);
	std::cout << "Loading " << ModName << " ... " << std::endl;
//Fucking NT Kernel...
#if WIN_BUILD
	HMODULE mod_lib = LoadLibrary(thisMod.c_str());
	if(!mod_lib){
		std::cout << "Module failed to load properly." << std::endl;
		return;
	}
#else
	void *mod_lib = dlopen(thisMod.c_str(),RTLD_NOW);
	if(!mod_lib){
		std::cout << dlerror() << std::endl;
		return;
	}
#endif
	std::cout << stringMod(S1Prefix,"Found library. Verifying that module exports required functions...") << std::endl;
	std::cout << SectionScope << std::endl;
#if WIN_BUILD

#else
	char* errorLog = NULL;
	dlerror();
	typedef void (*func_t)(void);
	std::cout << stringMod(SectionItem,"Initialization Function: ");
	func_t init = (func_t) dlsym(mod_lib,"initialize");
	if((errorLog = dlerror()) != NULL) std::cout << errorLog << std::endl;
	else std::cout << "Verified." << std::endl;
	errorLog = NULL;
	std::cout << stringMod(SectionItem,"Update Function: ");
	func_t update = (func_t) dlsym(mod_lib,"update");
	if((errorLog = dlerror()) != NULL) std::cout << errorLog << std::endl;
	else std::cout << "Verified." << std::endl;
	if(init && update){
		std::cout << stringMod(SectionItem,"Loading Module into catalog...") << std::endl;
		std::cout << SectionDecrease << std::endl;
		ModList.push_front(new Module(ModName,mod_lib,init,update));
		return;
	}
#endif
	std::cout << "A required symbol was not located. Module will not be added to catalog." << std::endl;
}