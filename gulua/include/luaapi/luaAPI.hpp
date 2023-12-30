#ifndef LUA_API_
#define LUA_API_

// Lua Headers
#include <string>
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

#include "luaapi/luaAPI_entitylib.hpp"
#include "luaapi/luaAPI_hooklib.hpp"


#define LUA_TABLE_APPEND_STR_STR(L, KEY, VALUE, FUNCTION_IDX) { \
    lua_pushstring(L, KEY); \
	lua_pushstring(L, VALUE); \
	lua_settable(L, FUNCTION_IDX); \
}

#define LUA_TABLE_APPEND_STR_FUNC(L, KEY, VALUE, FUNCTION_IDX) { \
    lua_pushstring(L, KEY); \
	lua_pushcfunction(L, VALUE); \
	lua_settable(L, FUNCTION_IDX); \
}

namespace luaAPI {
	lua_State* loadLua(const char* fileName);
	void closeLua(lua_State *L);
	void stackDump(lua_State *L);
	void error(lua_State *L, const char *fmt, ...);
	void callGlobalFunction(lua_State *L, const char *func, const char *sig, 
		...);
	std::string retrieveEntIDFromTable(lua_State *L); // Assumes Entity Table is at top of stack
}

#endif