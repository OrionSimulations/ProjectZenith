#ifndef STELLA_FRAMEWORK
#define STELLA_FRAMEWORK

class StellaFramework;

namespace Stella{
	StellaFramework* init(const char* rootDir);
	void free(StellaFramework *thisFrame);
}

#endif