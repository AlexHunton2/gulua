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
	std::shared_ptr<TriangleEntity> tri_ent = std::make_shared<TriangleEntity>();

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
	std::shared_ptr<std::vector<Attr::Point>> _vertices = (triEnt->getVertices()->attrs);


	lua_newtable(L);
	int i = 1;
	for (auto pair : *_vertices) {
		lua_pushinteger(L, i);
		luaAttrs::point::push_point(L, pair.x, pair.y);
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
	std::shared_ptr<std::vector<Attr::Point>> _vertices = (triEnt->getVertices()->attrs);

	luaL_argcheck(L, argtype == "table" || argtype == "userdata", 2, "not point ot table");
	
	int i;
	if (argtype == "table") {
		for (i = 0; i < 3; i++) {
			lua_rawgeti(L, 2, i+1); // push all three points
		}
	}

	int j = argtype == "table" ? 1 : 0;
	Attr::Point *pt_ptr;
	_vertices->clear();
	for (int i = 0; i < 3; i++) {
		pt_ptr = luaAttrs::point::check_point(L, i+2+j);
		_vertices->push_back(*pt_ptr);
	}
	return 0;
}

lua_method get_color(lua_State *L) {
	LuaEntity *ent = check_triangle(L);
	std::string id = std::string(ent->id);

	std::shared_ptr<TriangleEntity> triEnt = std::dynamic_pointer_cast<TriangleEntity>(EntityRegistry::getInstance()->get(id));
	if (!triEnt) {
		return 1;
	}
	std::shared_ptr<Attr::Color> _color = triEnt->getColor();

	lua_newtable(L);
	for (int i = 0; i < 3; i++) {
		lua_pushinteger(L, i+1);
		luaAttrs::color::push_color(L, _color->r, _color->g, _color->b, _color->a);
		lua_settable(L, -3);
	}

	return 1;
}

// set_color(table(r, g, b, a)) or set_color(r, g, b ,a)
lua_method set_color(lua_State *L) {
	LuaEntity *ent = check_triangle(L);
	std::string id = std::string(ent->id);
	std::string argtype = std::string(luaL_typename(L, 2));

	std::shared_ptr<TriangleEntity> triEnt = std::dynamic_pointer_cast<TriangleEntity>(EntityRegistry::getInstance()->get(id));
	
	if (!triEnt) {
		return 1;
	}
	std::shared_ptr<Attr::Color> _color = triEnt->getColor();

	luaL_argcheck(L, argtype == "table" || argtype == "number" || argtype == "userdata", 2, "not number ot table or color");
	
	if (argtype == "userdata") {
		Attr::Color *color = luaAttrs::color::check_color(L, 2);
		_color->r = color->r; _color->g = color->g; _color->b = color->b; _color->a = color->a;
		return 0;
	}

	if (argtype == "table") {
		for (int i = 0; i < 4; i++) {
			lua_rawgeti(L, 2, i+1); // push all four numbers
		}
	}

	int j = argtype == "table" ? 1 : 0;
	int r, g, b, a;
	r = luaL_checknumber(L, j+2);
	luaL_argcheck(L, r >= 0 && r <= 255, j+2, "invalid red size");
	_color->r = r;
	g = luaL_checknumber(L, j+3);
	luaL_argcheck(L, g >= 0 && g <= 255, j+3, "invalid green size");
	_color->g = g;
	b = luaL_checknumber(L, j+4);
	luaL_argcheck(L, b >= 0 && b <= 255, j+4, "invalid blue size");
	_color->b = b;
	a = luaL_checknumber(L, j+5);
	luaL_argcheck(L, a >= 0 && a <= 100, j+5, "invalid alpha size");
	_color->a = a;
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