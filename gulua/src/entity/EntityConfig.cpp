#include "entity/LuaEntity.hpp"

std::map<std::string, std::shared_ptr<EntityType>> ent_type_map = std::map<std::string, std::shared_ptr<EntityType>>();

int init_ent_type_map() {
	// Register Entiy Types

	// Triangle
	std::shared_ptr<EntityType> tri = std::make_shared<EntityType>();
	tri->luaopen_entlib = luaopen_trianglelib;
	tri->create_func = luaEnts::_triangle::_create;
	ent_type_map.insert({"Triangle", tri});

	return GULUA_OK;
}