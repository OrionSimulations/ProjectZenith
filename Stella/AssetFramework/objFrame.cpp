#include "objFrame.h"

//Asset Framework Definitions

void AssetFramework::loadAssetLibrary(const char* LibName){
	for(auto it = AssetLibList.begin(); it != AssetLibList.end(); it++){
		if((**it).getName() == LibName){
			std::cout << "Asset Library already loaded." << std::endl;
			return;
		}
	}
}

void AssetFramework::updateAssetLibraryList(){

}

void AssetFramework::instantiateAsset(AssetLibrary srcLib, std::string className){

}

void AssetFramework::autoLoadAssetLibraries(){
	
}
