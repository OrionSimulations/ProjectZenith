#ifndef CONTENTLOAD
#define CONTENTLOAD

#include <iostream>
#include <list>
#include <dirent.h>
#include <cstring>

#include "sysenv.h"

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
	std::list<const char*> requiredFuncs;

	//Content Loading Methods
	void loadContent(const char* contentDir, const char* contentName){
//Fucking NT Kernel...
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
		for(auto it = requiredFuncs.begin(); it != requiredFuncs.end(); ++it){
			std::cout << Section::stringSec(2,Section::Item,std::string(strcat(strcpy(functionLog,*it),": ")));
			funcList.push_front((func_t)dlsym(con_lib,*it));
			if((errorLog = dlerror()) != NULL) std::cout << errorLog << std::endl;
			else std::cout << "Verified." << std::endl;
			errorLog = NULL;
		}
		delete functionLog;
		if(funcList.size() > 0){
			std::cout << Section::stringSec(2,Section::Item,"Loading Module into catalog...") << std::endl;
			std::cout << Section::stringSec(2,Section::Decrease) << std::endl;
			contentInstances.push_front(new T_Container(contentName,con_lib,funcList));
			return;
		}
#endif
		std::cout << "A required symbol was not located. Module will not be added to catalog." << std::endl;
	}
	void scanDir(){
		DIR *progDir = opendir(contentRoot);																	//Open Directory
		struct dirent *dirRoot;																					//Allocate Directory Struct
		if(progDir){
			dirRoot = readdir(progDir);																			//Skip Parent Directory
			dirRoot = readdir(progDir);																			//Skip Current Directory
			char* content = NULL;
			while(dirRoot = readdir(progDir)){																	//Read Next Directory
				if(dirRoot->d_type & DT_DIR){
					content = dirRoot->d_name;
					checkDirCfg(content);
				}
			}
			closedir(progDir);
		}
	}
	void checkDirCfg(const char* contentName){ 
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
		char* fileEXT;																			//Allocate library extension
		char* tmp;
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
	ContentLoader(const char* sourceDir, std::list<const char*> &contentRequirements) : contentRoot(sourceDir), requiredFuncs(contentRequirements){
		std::cout << "Creating Content Loader" << std::endl;
		scanDir();
	}
	~ContentLoader(){
		std::cout << "Destroying Content Loader..." << std::endl;
	}
	std::list<T_Container*> exportContentList(){return contentInstances;}
	void importContentList(std::list<T_Container> list){contentInstances = list;}
};

#endif