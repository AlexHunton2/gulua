#ifndef HOOK
#define HOOK

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <string>

class Hook {
public:
	virtual void call(lua_State *L) {};
protected:
	Hook();
	~Hook();
	std::string mIdentifier;
	std::string mFunctionName;
};


#endif