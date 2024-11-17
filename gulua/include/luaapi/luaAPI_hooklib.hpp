#ifndef LUA_API_HOOKLIB_
#define LUA_API_HOOKLIB_

// Lua Headers
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <stdio.h>
#include <math.h>
#include <vector>
#include <memory>

#include "lua.h"
#include "luaapi/luaAPI.hpp"

#include "entity/EntityRegistry.hpp"
#include "hook/HookRegistry.hpp"

namespace luaAPI {
namespace _hooklib {
    // Args: "Identifier, Hookname, Function"
    int register_hook(lua_State *L);
    const struct luaL_Reg hooklib [] = {
        {"register_hook", register_hook},
        {NULL, NULL}  /* sentinel */
    };
}
}

int luaopen_hooklib(lua_State *L);

#endif
