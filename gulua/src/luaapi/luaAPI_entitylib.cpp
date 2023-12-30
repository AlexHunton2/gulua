#include "luaapi/luaAPI_entitylib.hpp"
#include "lua.h"
#include "luaapi/luaAPI.hpp"

int luaopen_entitylib(lua_State *L) {
	luaL_newlib(L, luaAPI::_entitylib::entitylib);
	return 1;
}

// Entity Library Functions:
int luaAPI::_entitylib::test_func(lua_State *L) {
	return 1;
}

int luaAPI::_entitylib::create_triangle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TTABLE); // ensure first param is table

	// push all vertices in table to stack
	for (int i=1; i < 7; i++) {
		lua_rawgeti(L, 1, i);
	}

	// retrieve all vertices
	// skip table index, (1 = table, 2 = first vertex, .. 7 = last vertex)
	std::vector<std::pair<int, int>> vertices;
	for (int i=2; i < 8; i+= 2) {
		int x = luaL_checknumber(L, i);
		int y = luaL_checknumber(L, i+1);
		vertices.push_back({x, y});
	}


	std::shared_ptr<EntityRegistry> ent_reg = EntityRegistry::getInstance();
	std::shared_ptr<Entity> tri_ent = std::make_shared<TriangleEntity>(vertices);
    std::string tri_id = ent_reg->add(tri_ent);

    lua_pop(L, 7);
    
	tri_ent->emit(L);
	return 1;
}
 
