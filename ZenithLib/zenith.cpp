#include "zenith.h"
#include "EngineConfig.h"
#include "sysenv.h"
#include "Frameworks/ModuleFramework/modLoad.h"
#include "Frameworks/AssetFramework/objFrame.h"
#include "Frameworks/AbstractionFramework/absFrame.h"
#include "Frameworks/RenderingFramework/renFrame.h"

std::string buildEnv::BuildDir;
std::string buildEnv::ModDir;
std::string buildEnv::AssetDir;
char buildEnv::dirDelim;
const char* Section::S1Prefix;
const char* Section::Increase;
const char* Section::Item;
const char* Section::Decrease;

class ZenithFramework{
	ModuleFramework *moduleFrame;
	AssetFramework *assetFrame;
	AbstractionFramework *absFrame;
	RenderingFramework *renderFrame;

	void initEnv(const char* rootDir);

public:
	ZenithFramework(const char* rootDir);
	~ZenithFramework();
};

ZenithFramework::ZenithFramework(const char* rootDir){
	initEnv(rootDir);
	moduleFrame = new ModuleFramework();
	assetFrame = new AssetFramework();
	absFrame = new AbstractionFramework();
	renderFrame = new RenderingFramework();
}

ZenithFramework::~ZenithFramework(){
	delete renderFrame;
	delete absFrame;
	delete assetFrame;
	delete moduleFrame;
}

void ZenithFramework::initEnv(const char* rootDir){
    std::string version = "Zenith Engine: v. ";
    version.append(Engine_Version);
    std::cout << version << std::endl;
    
#if WIN_BUILD
	buildEnv::dirDelim = '\\';
#else
	buildEnv::dirDelim = '/';
#endif
	buildEnv::BuildDir = std::string(rootDir);
	buildEnv::ModDir = buildEnv::BuildDir.substr(0,buildEnv::BuildDir.rfind(buildEnv::dirDelim)+1)+"modules"+buildEnv::dirDelim;
	buildEnv::AssetDir = buildEnv::BuildDir.substr(0,buildEnv::BuildDir.rfind(buildEnv::dirDelim)+1)+"assets"+buildEnv::dirDelim;
	Section::S1Prefix = " - ";
	Section::Increase = "\\ ";
	Section::Item = "| ";
	Section::Decrease = "/ ";
}

//Library Calls
namespace Zenith {
    ZenithFramework* init(const char* rootDir){return new ZenithFramework(rootDir);}

    void free(ZenithFramework *thisFrame){
        delete thisFrame;
        return;
    }
}