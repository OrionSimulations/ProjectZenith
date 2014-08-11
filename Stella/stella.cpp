#include "stella.h"
#include "EngineConfig.h"
#include "sysenv.h"
#include "ModuleFramework/modLoad.h"
#include "AssetFramework/objFrame.h"
#include "AbstractionFramework/absFrame.h"
#include "RenderingFramework/renFrame.h"

std::string buildEnv::BuildDir;
std::string buildEnv::ModDir;
std::string buildEnv::AssetDir;
char buildEnv::dirDelim;
const char* Section::S1Prefix;
const char* Section::Increase;
const char* Section::Item;
const char* Section::Decrease;

class StellaFramework{
	ModuleFramework *moduleFrame;
	AssetFramework *assetFrame;
	AbstractionFramework * absFrame;
	RenderingFramework *renderFrame;

	void initEnv(const char* rootDir);

public:
	StellaFramework(const char* rootDir);
	~StellaFramework();
};

StellaFramework::StellaFramework(const char* rootDir){
	initEnv(rootDir);
	moduleFrame = new ModuleFramework();
	assetFrame = new AssetFramework();
	absFrame = new AbstractionFramework();
	renderFrame = new RenderingFramework();
}

StellaFramework::~StellaFramework(){
	delete renderFrame;
	delete absFrame;
	delete assetFrame;
	delete moduleFrame;
}

void StellaFramework::initEnv(const char* rootDir){
    std::string version = "Stella Engine: v. ";
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
namespace Stella{
    StellaFramework* init(const char* rootDir){return new StellaFramework(rootDir);}

    void free(StellaFramework *thisFrame){
        delete thisFrame;
        return;
    }
}