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
	void call(lua_State *L, const char *sig, ...);
	void call(lua_State *L, const char *sig, va_list args);
	Hook(std::string ident, std::string sig, int key) 
		: mCallSignature(sig), mIdentifier(ident), mLuaRegistryKey(key) {};
	std::string mCallSignature; 
protected:
	std::string mIdentifier;
	int mLuaRegistryKey;
};


#endif