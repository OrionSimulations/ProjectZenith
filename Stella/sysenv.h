#ifndef SYSENV
#define SYSENV

#include <string>

struct buildEnv{
	static std::string BuildDir;
	static std::string ModDir;
	static std::string AssetDir;
	static char dirDelim;
};

struct Section{
	static const char* S1Prefix;
	static const char* Increase;
	static const char* Item;
	static const char* Decrease;
	static std::string stringMod(const char* prefix, std::string BaseString){
		return prefix+BaseString;
	}
	static std::string stringSec(short scope, const char* direction,std::string BaseString = ""){
		if(scope == 1) return Section::S1Prefix + BaseString;
		else{
			std::string returnVal;
			for(short i=1; i<scope; i++){
				returnVal += "   ";
			}
			returnVal += direction+BaseString;
			return returnVal;
		}
	}
};

#endif