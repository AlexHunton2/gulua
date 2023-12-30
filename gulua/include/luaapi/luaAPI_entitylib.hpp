#ifndef LUA_API_ENTITYLIB_
#define LUA_API_ENTITYLIB_

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
#include "luaapi/luaAPI.hpp"

#include "entity/EntityRegistry.hpp"

namespace luaAPI {
namespace _entitylib {
	int test_func(lua_State *L);
	// Args: table: {ax, ay, bx, by, cx, cy}
	int create_triangle(lua_State *L);
	const struct luaL_Reg entitylib [] = {
        {"test_func", test_func},
        {"create_triangle", create_triangle},
        {NULL, NULL}  /* sentinel */
	};
}
}

int luaopen_entitylib(lua_State *L);

#endif