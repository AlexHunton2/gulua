/*
    LuaEntity.hpp

    Responsible for exposing entities to lua
*/
#ifndef LUA_ENTITY_
#define LUA_ENTITY_

#include <iostream>

#include "entity/Entity.hpp"
#include "entity/EntityRegistry.hpp"
#include "luaapi/luaDefs.hpp"
#include "attribute/Attribute.hpp"
#include "attribute/LuaAttribute.hpp"

#include "util/util.hpp"

#define ENT_STR_SIZE 64

#define DEFINE_LUA_ACCESSOR_METHOD(method_name, generic_function, attr_name) \
lua_method method_name(lua_State* L) {                  \
    return generic_function(L, attr_name);         \
}

typedef struct LuaEntity {
    char id[ENT_STR_SIZE]; // Index to EntityRegistery
    char type[ENT_STR_SIZE]; // Index to ent_type_map
} LuaEntity;

typedef struct EntityType {
    int (*luaopen_entlib)(lua_State *L); // library func
    int (*create_func)(lua_State *L); // create entity, return # of data pushed
} EntityType;

extern std::map<std::string, std::shared_ptr<EntityType>> ent_type_map;
extern int init_ent_type_map();

namespace luaEnts {
namespace _polygon {
    LuaEntity *check_polygon(lua_State *L);

    lua_method generic_get_str(lua_State* L, const char* attr_name);
    lua_method generic_set_str(lua_State* L, const char* attr_name);

    lua_method generic_get_int(lua_State* L, const char* attr_name);
    lua_method generic_set_int(lua_State *L, const char* attr_name, int min, int max);

    lua_method generic_get_color(lua_State *L, const char* attr_name);
    lua_method generic_set_color(lua_State *L, const char* attr_name);

    lua_method get_color(lua_State *L);
    lua_method set_color(lua_State *L);
    lua_method get_text(lua_State*L);
    lua_method set_text(lua_State *L);
    lua_method get_textcolor(lua_State *L);
    lua_method set_textcolor(lua_State *L);
}

namespace _triangle {
    int _create(lua_State *L);

    lua_method get_vertices(lua_State *L);
    lua_method set_vertices(lua_State *L);

    static const struct luaL_Reg trianglelib_f [] = {
      {NULL, NULL}
    };
    static const struct luaL_Reg trianglelib_m [] = {
        {"get_vertices", _triangle::get_vertices},
        {"set_vertices", _triangle::set_vertices},
        {"get_color", _polygon::get_color},
        {"set_color", _polygon::set_color},
        {"get_text", _polygon::get_text},
        {"set_text", _polygon::set_text},
        {"get_textcolor", _polygon::get_textcolor},
        {"set_textcolor", _polygon::set_textcolor},
        {NULL, NULL}
    };
}

namespace _rectangle {
    int _create(lua_State *L);

    lua_method get_position(lua_State *L);
    lua_method set_position(lua_State *L);

    lua_method get_width(lua_State *L);
    lua_method set_width(lua_State *L);

    lua_method get_height(lua_State *L);
    lua_method set_height(lua_State *L);

    static const struct luaL_Reg rectanglelib_f [] = {
      {NULL, NULL}
    };
    static const struct luaL_Reg rectanglelib_m [] = {
        {"get_position", get_position},
        {"set_position", set_position},
        {"get_width", get_width},
        {"set_width", set_width},
        {"get_height", get_height},
        {"set_height", set_height},
        {"get_color", _polygon::get_color},
        {"set_color", _polygon::set_color},
        {"get_text", _polygon::get_text},
        {"set_text", _polygon::set_text},
        {"get_textcolor", _polygon::get_textcolor},
        {"set_textcolor", _polygon::set_textcolor},
        {NULL, NULL}
    };
}
}

int luaopen_trianglelib(lua_State *L);
int luaopen_rectanglelib(lua_State *L);

#endif
