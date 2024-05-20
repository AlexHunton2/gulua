#ifndef LUA_API_ATTRLIB_
#define LUA_API_ATTRLIB_

// Lua Headers
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <stdio.h>
#include <math.h>
#include <vector>

#include "lua.h"

namespace luaAPI {
namespace _attrlib {
	const struct luaL_Reg nulllib [] = {
        {NULL, NULL}  /* sentinel */
	};
}
}

int luaopen_attrlib(lua_State *L);

#endif