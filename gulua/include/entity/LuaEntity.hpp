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

#define ENT_STR_SIZE 32

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
namespace _triangle {
	LuaEntity *check_triangle(lua_State *L);

	int _create(lua_State *L);

	lua_method get_vertices(lua_State *L);
	lua_method set_vertices(lua_State *L);
	lua_method get_color(lua_State *L);
	lua_method set_color(lua_State *L);
	static const struct luaL_Reg trianglelib_f [] = {
      {NULL, NULL}
    };
	static const struct luaL_Reg trianglelib_m [] = {
      {"get_vertices", get_vertices},
      {"set_vertices", set_vertices},
      {"get_color", get_color},
      {"set_color", set_color},
      {NULL, NULL}
    };
}
}

int luaopen_trianglelib(lua_State *L);

#endif