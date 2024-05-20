#include "luaapi/luaAPI_entitylib.hpp"

int luaopen_entitylib(lua_State *L) {
	luaL_newlib(L, luaAPI::_entitylib::entitylib);
	return 1;
}

// Entity Library Functions:
lua_lib_func luaAPI::_entitylib::_create(lua_State *L) {
	std::string ent_name = std::string(luaL_checkstring(L, 1));
	std::shared_ptr<EntityType> ent_type = ent_type_map[ent_name];
	if (ent_type != NULL) {
		lua_pop(L, 1);
		return ent_type->create_func(L);
	}

	lua_pop(L, 1);
	lua_pushnil(L);
	return 1;
}

lua_lib_func luaAPI::_entitylib::_delete(lua_State *L) {
	LuaEntity* ent = (LuaEntity *)lua_touserdata(L, 1);
	luaL_argcheck(L, ent != NULL, 1, "`Entity' expected");
	std::string id = std::string(ent->id);

	/*
	Note: currently don't need a individual delete function but you have
	LuaEntity.type to do this so, go ahead if you need it idk.
	*/

	std::shared_ptr<EntityRegistry> ent_reg = EntityRegistry::getInstance();
	ent_reg->remove(std::string(id));
	return 1;
}
 
