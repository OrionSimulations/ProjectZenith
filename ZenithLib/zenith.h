#ifndef ZENITH_FRAMEWORK
#define ZENITH_FRAMEWORK

class ZenithFramework;

namespace Zenith {
	ZenithFramework* init(const char* rootDir);
	void free(ZenithFramework *thisFrame);
}

#endif