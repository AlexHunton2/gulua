#include "entity/LuaEntity.hpp"

namespace luaEnts {
namespace _triangle {

LuaEntity *check_triangle(lua_State *L) {
	void *ud = luaL_checkudata(L, 1, "Gulua.Triangle");
	luaL_argcheck(L, ud != NULL, 1, "`Triangle' expected");
	return (LuaEntity *)ud;
}

int _create(lua_State *L) {
	// create TriangleEntity
	std::vector<std::pair<int, int>> vertices;
	for (int i=0; i < 3; i++) {
		vertices.push_back({0, 0});
	}

	std::shared_ptr<Entity> tri_ent = std::make_shared<TriangleEntity>(vertices);

	// Register TriangleEntity
	std::shared_ptr<EntityRegistry> ent_reg = EntityRegistry::getInstance();
	std::string tri_id = ent_reg->add(tri_ent);
	
	// Update Lua Entity
	LuaEntity *lua_ent = (LuaEntity *)lua_newuserdata(L, sizeof(LuaEntity));
	luaL_getmetatable(L, "Gulua.Triangle");
  	lua_setmetatable(L, -2);

	strncpy(lua_ent->id, tri_id.c_str(), ENT_STR_SIZE-1);

	const char* triangle_type_name = "Triangle";
	strncpy(lua_ent->type, triangle_type_name, ENT_STR_SIZE-1);

	return 1;
}

lua_method get_vertices(lua_State *L) {
	LuaEntity *ent = check_triangle(L);
	std::string id = std::string(ent->id);

	std::shared_ptr<TriangleEntity> triEnt = std::dynamic_pointer_cast<TriangleEntity>(EntityRegistry::getInstance()->get(id));
	if (!triEnt) {
		return 1;
	}

	lua_newtable(L);
	int i = 1;
	for (std::pair<int, int> pair : triEnt->mVertices) {
		lua_pushinteger(L, i);
		luaAttrs::point::push_point(L, pair.first, pair.second);
		lua_settable(L, -3);
		i++;
	}

	return 1;
}

lua_method set_vertices(lua_State *L) {
	LuaEntity *ent = check_triangle(L);
	std::string id = std::string(ent->id);
	std::string argtype = std::string(luaL_typename(L, 2));
	
	std::shared_ptr<TriangleEntity> triEnt = std::dynamic_pointer_cast<TriangleEntity>(EntityRegistry::getInstance()->get(id));
	if (!triEnt) {
		return 1;
	}

	luaL_argcheck(L, argtype == "table" || argtype == "userdata", 2, "not point ot table");
	
	int i;
	if (argtype == "table") {
		for (i = 0; i < 3; i++) {
			lua_rawgeti(L, 2, i+1); // push all three points
		}
	}

	int j = argtype == "table" ? 1 : 0;
	Attr::Point *pt_ptr;
	triEnt->mVertices.clear();
	for (int i = 0; i < 3; i++) {
		pt_ptr = luaAttrs::point::check_point(L, i+2+j);
		triEnt->mVertices.push_back({pt_ptr->x, pt_ptr->y});
	}
	return 0;
}

}
}

int luaopen_trianglelib(lua_State *L) {
	luaL_newmetatable(L, "Gulua.Triangle");

	lua_pushvalue(L, -1);  /* duplicate the metatable */
	lua_setfield(L, -2, "__index");  /* mt.__index = mt */
	luaL_setfuncs(L, luaEnts::_triangle::trianglelib_m, 0);  /* register metamethods */
	luaL_newlib(L, luaEnts::_triangle::trianglelib_m);  /* create lib table */

	return 1;
}