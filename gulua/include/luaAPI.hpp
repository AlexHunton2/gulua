#ifndef LUA_API_
#define LUA_API_

// Lua Headers
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

namespace luaAPI {
	void loadLua(const char* fileName);
	void stackDump(lua_State *L);
	void error(lua_State *L, const char *fmt, ...);
}

#endif