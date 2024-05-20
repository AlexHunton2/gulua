#ifndef LUA_API_
#define LUA_API_
#pragma once

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
#include <locale>

#include "luaapi/luaAPI_hooklib.hpp"
#include "luaapi/luaAPI_entitylib.hpp"
#include "entity/LuaEntity.hpp"
#include "attribute/LuaAttribute.hpp"
#include "util/util.hpp"
#include "luaapi/luaDefs.hpp"

namespace luaAPI {
	lua_State* loadLua(const char* fileName);
	void closeLua(lua_State *L);
	void stackDump(lua_State *L);
	void error(lua_State *L, const char *fmt, ...);
	void callGlobalFunction(lua_State *L, const char *func, const char *sig, 
		...);
}

#endif