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
#include <iostream>

#include "lua.h"
#include "luaapi/luaAPI.hpp"
#include "entity/EntityRegistry.hpp"

namespace luaAPI {
namespace _entitylib {
	int _create(lua_State *L);
	int _delete(lua_State *L);
	const struct luaL_Reg entitylib [] = {
        {"create", _create},
        {"delete", _delete},
        {NULL, NULL}  /* sentinel */
	};
}
}

int luaopen_entitylib(lua_State *L);

#endif