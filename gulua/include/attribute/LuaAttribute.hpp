#ifndef LUA_ATTRIBUTE_
#define LUA_ATTRIBUTE_
#pragma once

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "gulua.hpp"
#include <cstddef>
#include <iostream>
#include <map>

#include "luaapi/luaDefs.hpp"
#include "attribute/Attribute.hpp"

typedef struct AttributeType {
    int (*luaopen_entlib)(lua_State *L); // library func
} AttributeType;

extern std::map<std::string, std::shared_ptr<AttributeType>> attr_type_map;
extern int init_attr_type_map();

// Attribute : Point
namespace luaAttrs {
namespace point {
    #define LUA_PT_META_NAME "Gulua.Point"
    #define LUA_PT_META_LIB_NAME "Gulua.Lib.Point"

    Attr::Point *check_point(lua_State *L);
    Attr::Point *check_point(lua_State *L, int n);
    Attr::Point *push_point(lua_State *L, int x, int y);

    lua_method _new(lua_State* L);
    lua_method _index(lua_State *L); // pt[""]
    lua_method _newindex(lua_State *L); // pt[""] = ?
    lua_method _set(lua_State *L); // pt.set(x, y)
    lua_method _call(lua_State *L); // calls new()

    // helper function
    static void set_x_y(lua_State *L, Attr::Point *pt_ptr, int x, int y);

    const struct luaL_Reg pointlib_f [] = { // library methods
        {"new", _new},
        {NULL, NULL}
    };
    const struct luaL_Reg pointlib_lm [] = { // library metamethods
        {"__call", _call},
        {NULL, NULL}
    };
    const struct luaL_Reg pointlib_m [] = { // object methods
        {"__index", _index},
        {"__newindex", _newindex},
        {"set", _set},
        {NULL, NULL}
    };
}
}
int luaopen_pointlib(lua_State *L);

#endif