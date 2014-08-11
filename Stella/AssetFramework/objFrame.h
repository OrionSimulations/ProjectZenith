#ifndef OBJFRAME
#define OBJFRAME

#include <list>
#include <set>
#include <string>
#include <iostream>
#include <sstream>
// #include <glog/logging.h>

#include "../contentLoad.h"

class AssetLibrary{
	static int nextLibID;
	int libID;
	const char* libName;
	long objInstances;
	void* obj_lib;
	typedef void (*func_t)();
	func_t lib_init;

public:
	AssetLibrary(const char* newName, void* objLibrary, func_t init) : libName(newName), obj_lib(objLibrary), lib_init(init){(*lib_init)(); nextLibID++;}
	~AssetLibrary(){
		std::cout << "Unloading Asset Library " << this->libName << "..." << std::endl;
		//Magic goes here
		
		//
		this->obj_lib = NULL;
	}
	void refCountUp(){objInstances++;}
	void refCountDn(){objInstances--; if(objInstances<=0) delete this;}				//In theory, this SHOULD delete the library ref when all instances are deleted
	long refCount(){return objInstances;}
	const char* getName(){return libName;}
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
    	//Magic goes here

    	//
    }
    ~AssetFramework(){
    	std::cout << "Destroying Asset Framework..." << std::endl;
    	//Magic goes here

    	//
    }
};

#endif