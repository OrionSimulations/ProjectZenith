#ifndef SYSENV
#define SYSENV

#include <string>
#include <cstring>

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

class AutoSection{
	static const short maxLevel = 5;
	short level;
	
	public:
	AutoSection(){level = 0;}
	~AutoSection(){}

	AutoSection& operator++(){
		this->level++;
		return *this;
	}
	AutoSection operator++(int){
		AutoSection newSec(*this);
		++(*this);
		return newSec;
	}

	char* printSection(){
		char* tmp = (char*)malloc(2*level+3);
		memset(tmp,'=',sizeof(tmp)/sizeof(char));
		*tmp = '|';
		tmp[2*level+2] = '>';
		return tmp;
	}

};

#endif