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
    std::string (*to_string)(Attr::Attribute *attr);
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
    std::string to_string(Attr::Attribute *attr);

    lua_method _new(lua_State* L);
    lua_method _index(lua_State *L); // pt[""]
    lua_method _newindex(lua_State *L); // pt[""] = ?
    lua_method _set(lua_State *L); // pt.set(x, y)
    lua_method _call(lua_State *L); // calls new()
    lua_method _tostring(lua_State *L);

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
        {"__tostring", _tostring},
        {"set", _set},
        {NULL, NULL}
    };
}
}
int luaopen_pointlib(lua_State *L);

// Attribute : Color
namespace luaAttrs {
namespace color {
    #define LUA_CLR_META_NAME "Gulua.Color"
    #define LUA_CLR_META_LIB_NAME "Gulua.Lib.Color"

    Attr::Color *check_color(lua_State *L);
    Attr::Color *check_color(lua_State *L, int n);
    Attr::Color *push_color(lua_State *L, int r, int g, int b, int a);
    std::string to_string(Attr::Attribute *attr);

    lua_method _new(lua_State* L);
    lua_method _index(lua_State *L); // clr[""]
    lua_method _newindex(lua_State *L); // clr[""] = ?
    lua_method _set(lua_State *L); // clr.set(r, g, b, a)
    lua_method _call(lua_State *L); // calls new()
    lua_method _tostring(lua_State *L);

    const struct luaL_Reg colorlib_f [] = { // library methods
        {"new", _new},
        {NULL, NULL}
    };
    const struct luaL_Reg colorlib_lm [] = { // library metamethods
        {"__call", _call},
        {NULL, NULL}
    };
    const struct luaL_Reg colorlib_m [] = { // object methods
        {"__index", _index},
        {"__newindex", _newindex},
        {"__tostring", _tostring},
        {"set", _set},
        {NULL, NULL}
    };
}
}
int luaopen_colorlib(lua_State *L);


#endif
