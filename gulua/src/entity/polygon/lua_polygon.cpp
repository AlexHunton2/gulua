#include "entity/LuaEntity.hpp"

#define NUM_OF_COLOR_CHANNELS 4

namespace luaEnts {
namespace _polygon {

LuaEntity *check_polygon(lua_State *L) {
	void *_ud = lua_touserdata(L, 1);
	char *type_name = ((LuaEntity *)_ud)->type;

	void *ud = luaL_checkudata(L, 1, util_format("Gulua.%s", type_name).c_str());
	luaL_argcheck(L, ud != NULL, 1, util_format("`%s' expected", type_name).c_str());
	return (LuaEntity *)ud;
}

lua_method get_color(lua_State *L) {
	LuaEntity *ent = check_polygon(L);
	std::string id = std::string(ent->id);

	std::shared_ptr<PolygonEntity> polyEnt = std::dynamic_pointer_cast<PolygonEntity>(EntityRegistry::getInstance()->get(id));
	if (polyEnt == nullptr) {
		return 1;
	}
	std::shared_ptr<Attr::Color> _color = polyEnt->getColor();

	lua_newtable(L);
	for (int i = 0; i < NUM_OF_COLOR_CHANNELS-1; i++) {
		lua_pushinteger(L, i+1);
		luaAttrs::color::push_color(L, _color->r, _color->g, _color->b, _color->a);
		lua_settable(L, -3);
	}

	return 1;
}

// set_color(table(r, g, b, a)) or set_color(r, g, b ,a)
lua_method set_color(lua_State *L) {
	LuaEntity *ent = check_polygon(L);
	std::string id = std::string(ent->id);
	std::string argtype = std::string(luaL_typename(L, 2));

	std::shared_ptr<PolygonEntity> polyEnt = std::dynamic_pointer_cast<PolygonEntity>(EntityRegistry::getInstance()->get(id));
	
	if (polyEnt == nullptr) {
		return 1;
	}
	std::shared_ptr<Attr::Color> _color = polyEnt->getColor();

	luaL_argcheck(L, argtype == "table" || argtype == "number" || argtype == "userdata", 2, "not number ot table or color");
	
	if (argtype == "userdata") {
		Attr::Color *color = luaAttrs::color::check_color(L, 2);
		_color->r = color->r; _color->g = color->g; _color->b = color->b; _color->a = color->a;
		return 0;
	}

	if (argtype == "table") {
		for (int i = 0; i < NUM_OF_COLOR_CHANNELS; i++) {
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