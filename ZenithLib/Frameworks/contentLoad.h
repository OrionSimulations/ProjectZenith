#ifndef CONTENTLOAD
#define CONTENTLOAD

#include <iostream>
#include <list>
#include <dirent.h>
#include <cstring>

#include "../sysenv.h"

#if WIN_BUILD
#include <windows.h>
#else
#include <dlfcn.h>
#endif

//Content Loading Class
//T_Container: Container Type for library instances.
template<typename T_Container>
class ContentLoader{
	//Library Properties
	const char* contentRoot;
	std::list<T_Container*> contentInstances;
	const char** requiredFuncs;

	//Content Loading Methods
	void loadContent(const char* contentDir, const char* contentName){
//Play well with the NT Kernel...
#if WIN_BUILD
		HMODULE con_lib = LoadLibrary(contentDir);
		if(!con_lib){
			std::cout << "Content failed to load properly." << std::endl;
			return;
		}
#else
		void *con_lib = dlopen(contentDir,RTLD_NOW);
		if(!con_lib){
			std::cout << dlerror() << std::endl;
			return;
		}
#endif
		std::cout << Section::stringSec(1,NULL,"Found library. Verifying that content exports required functions...") << std::endl;;
		std::cout << Section::stringSec(2,Section::Increase) << std::endl;
#if WIN_BUILD

#else
		char* errorLog = NULL;
		dlerror();
		typedef void (*func_t)(void);
		std::list<func_t> funcList;
		char* functionLog = new char[256];
		short i = 0;
		while(requiredFuncs[i] != NULL){
			std::cout << Section::stringSec(2,Section::Item,std::string(strcat(strcpy(functionLog,requiredFuncs[i]),": ")));
			funcList.push_back((func_t)dlsym(con_lib,requiredFuncs[i]));
			if((errorLog = dlerror()) != NULL) std::cout << errorLog << std::endl;
			else std::cout << "Verified." << std::endl;
			errorLog = NULL;
			i++;
		}
		delete functionLog;
		if(funcList.size() > 0){
			std::cout << Section::stringSec(2,Section::Item,"Loading content into catalog...") << std::endl;
			std::cout << Section::stringSec(2,Section::Decrease) << std::endl;
			contentInstances.push_front(new T_Container(contentName,con_lib,funcList));
			return;
		}
#endif
		std::cout << "A required symbol was not located. Content will not be added to catalog." << std::endl;
	}
	void scanDir(){
		std::cout << "Scanning Directory for Content..." << std::endl;
		DIR *progDir = opendir(contentRoot);
		struct dirent *dirRoot;
		if(progDir){
			char* content = NULL;
			int contentCount = 0;
			//Read Next Directory
			while(dirRoot = readdir(progDir)){
				if(dirRoot->d_type & DT_DIR){
					content = dirRoot->d_name;
					//Check if current content is either parent or self
					//strcmp returns 0 when identical
					if(strcmp(content,"..") && strcmp(content,".")){
						checkDirCfg(content);
						++contentCount;
					}
				}
			}
			closedir(progDir);
			std::cout << contentCount << " Modules loaded." << std::endl;
		}
	}
	void checkDirCfg(const char* contentName){
		std::cout << "Checking Directory Config..." << std::endl;
		for(auto it = contentInstances.begin(); it != contentInstances.end(); it++){
			if((**it).name == contentName){
				std::cout << "Content already loaded." << std::endl;
				return;
			}
		}
		DIR *contentDir = NULL;																					//Allocate Content Directory
		struct dirent *drnt;																					//Allocate Content Directory Struct
		char* content = new char[256];
		content = strcat(strcpy(content,contentRoot),contentName);
		char* file;																								//Allocate library path
		char* fileEXT;																							//Allocate library extension
		contentDir = opendir(content);																			//Open Content Directory
		while(drnt = readdir(contentDir)){
			file = drnt->d_name;
			//Check file extensions
			fileEXT = strrchr(file,'.');
			if(!strcmp(fileEXT,".so") || !strcmp(fileEXT,".dll")){
				content = strcat(strcat(content,&buildEnv::dirDelim),file);
				break;
			}
		}
		//TO BE IMPLEMENTED: Perform content configuration from files

		//
		closedir(contentDir);
		loadContent(content,contentName);
		delete content;
	}

public:
	ContentLoader(const char* sourceDir, const char** contentRequirements, bool firstScan=false) : contentRoot(sourceDir), requiredFuncs(contentRequirements){
		std::cout << "Creating Content Loader" << std::endl;
		if(firstScan) scanDir();
	}
	~ContentLoader(){
		std::cout << "Destroying Content Loader..." << std::endl;
	}
	std::list<T_Container*> exportContentList(){return contentInstances;}
	void importContentList(std::list<T_Container> list){contentInstances = list;}
};

#endif