#ifndef OBJFRAME
#define OBJFRAME

#include <list>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
// #include <glog/logging.h>

#include "../contentLoad.h"

struct AssetLibrary{
	static int nextLibID;
	int libID;
	const char* name;
	long objInstances;
	void* obj_lib;
	typedef void (*func_t)();
	func_t lib_init;

	AssetLibrary(const char* newName, void* objLibrary, std::list<func_t> funcList) : name(newName), obj_lib(objLibrary), lib_init(*(funcList.begin())){(*lib_init)(); nextLibID++;}
	~AssetLibrary(){
		std::cout << "Unloading Asset Library " << this->name << "..." << std::endl;
#if WIN_BUILD
		FreeLibrary(this->obj_lib);
#else
		if(dlclose(this->obj_lib)) std::cout << dlerror() << std::endl;
#endif
		this->obj_lib = NULL;
	}
	void refCountUp(){objInstances++;}
	void refCountDn(){objInstances--; if(objInstances<=0) delete this;}				//In theory, this SHOULD delete the library ref when all instances are deleted
	long refCount(){return objInstances;}
	const char* getName(){return name;}
};

class Property{
	const char* propName;
	void* prop_lib;

public:
	Property(const char* newName, void* propertySrc) : propName(newName), prop_lib(propertySrc){

	}
	~Property(){

	}
	const char* getName(){return propName;}
};

class AssetContainer{
	AssetLibrary srcLib;
	void* instance;
	std::list<Property*> PropList;

public:
	AssetContainer(AssetLibrary objLib, void* baseClass) : srcLib(objLib), instance(baseClass){srcLib.refCountUp();}
	~AssetContainer(){
		srcLib.refCountDn();
	}
	void injectProperty(Property &newProperty){PropList.push_front(&newProperty);}
	void removeProperty(Property &oldProperty){
		PropList.remove_if([oldProperty](Property const *ref){return ref==&oldProperty;});
	}
};

class AssetFramework{
	std::list<AssetLibrary*> AssetLibList;
	std::list<AssetContainer> AssetList;
    void loadAssetLibrary(const char* LibName);
    void updateAssetLibraryList();
    void instantiateAsset(AssetLibrary srcLib, std::string className);
    void autoLoadAssetLibraries();

public:
    AssetFramework(){
    	std::cout << "Creating Asset Framework..." << std::endl;
    	const char* reqFunc[] = {(char*)"initialize",(char*)"genAsset",NULL};
    	ContentLoader<AssetLibrary> assetLoader(buildEnv::AssetDir.c_str(),reqFunc,true);
    	AssetLibList = assetLoader.exportContentList();
    }
    ~AssetFramework(){
    	std::cout << "Destroying Asset Framework..." << std::endl;
    	for(AssetLibrary *ref : AssetLibList){
    		std::cout << "-";
    		delete ref;
    	}
    	
    }
};

#endif