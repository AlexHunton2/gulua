#include "attribute/LuaAttribute.hpp"

namespace luaAttrs {
namespace color {

Attr::Color *check_color(lua_State *L) {
	return check_color(L, 1);
}

Attr::Color *check_color(lua_State *L, int n) {
	void *ud = luaL_checkudata(L, n, LUA_CLR_META_NAME);
	luaL_argcheck(L, ud != NULL, 1, "`color' expected");
	return (Attr::Color *)ud;
}

// helper function
static void set_rgba(lua_State *L, Attr::Color *clr_ptr, int r, int g, int b, int a) {
	luaL_argcheck(L, r >= 0 && r <= 255, 1, "invalid red size");
	luaL_argcheck(L, g >= 0 && g <= 255, 1, "invalid green size");
	luaL_argcheck(L, b >= 0 && b <= 255, 1, "invalid blue size");
	luaL_argcheck(L, a >= 0 && a <= 100, 1, "invalid alpha size");
	clr_ptr->r = r; clr_ptr->g = g; clr_ptr->b = b; clr_ptr->a = a;
}

Attr::Color *push_color(lua_State *L, int r, int g, int b, int a) {
	Attr::Color *clr_ptr;
	clr_ptr = (Attr::Color *)lua_newuserdata(L, sizeof(Attr::Color));
	luaL_getmetatable(L, LUA_CLR_META_NAME);
	lua_setmetatable(L, -2);

	set_rgba(L, clr_ptr, r, g, b, a);
	return clr_ptr;
}

std::string to_string(Attr::Attribute *attr) {
	Attr::Color *clr_ptr = static_cast<Attr::Color *>(attr);
	// (x, y)
	return "(" + std::to_string(clr_ptr->r) + ", " + std::to_string(clr_ptr->g)
	+ ", " + std::to_string(clr_ptr->b) + ", " + std::to_string(clr_ptr->a) 
	+ ")"; 
}

// _new(x, y)
lua_method _new(lua_State *L) {
	int r, g, b, a; // inputs
	r = (int)luaL_checkinteger(L, 1);
	g = (int)luaL_checkinteger(L, 2);
	b = (int)luaL_checkinteger(L, 3);
	a = (int)luaL_checkinteger(L, 4);

	push_color(L, r, g, b, a);
	return 1;
}

lua_method _index(lua_State *L) {
	Attr::Color *clr_ptr;
	std::string key;

	clr_ptr = check_color(L);
	key = std::string(luaL_checkstring(L, 2));

	if (key == "r") {
		lua_pushinteger(L, clr_ptr->r);
		return 1;
	} else if (key == "g") {
		lua_pushinteger(L, clr_ptr->g);
		return 1;
	} else if (key == "b") {
		lua_pushinteger(L, clr_ptr->b);
		return 1;
	} else if (key == "a") {
		lua_pushinteger(L, clr_ptr->a);
		return 1;
	}

	return 0;
}

lua_method _newindex(lua_State *L) {
	Attr::Color *clr_ptr;
	std::string key;
	int val;

	clr_ptr = check_color(L);
	key = std::string(luaL_checkstring(L, 2));
	val = (int)luaL_checkinteger(L, 3);

	if (key == "r") {
		set_rgba(L, clr_ptr, val, clr_ptr->g, clr_ptr->b, clr_ptr->a);	
	} else if (key == "g") {
		set_rgba(L, clr_ptr, clr_ptr->r, val, clr_ptr->b, clr_ptr->a);
	} else if (key == "b") {
		set_rgba(L, clr_ptr, clr_ptr->r, clr_ptr->g, val, clr_ptr->a);
	} else if (key == "a") {
		set_rgba(L, clr_ptr, clr_ptr->r, clr_ptr->b, clr_ptr->b, val);
	}

	return 0;

}

lua_method _set(lua_State *L) {
	Attr::Color *clr_ptr;
	int r,g,b,a;

	clr_ptr = check_color(L);
	r = (int)luaL_checkinteger(L, 2);
	g = (int)luaL_checkinteger(L, 3);
	b = (int)luaL_checkinteger(L, 4);
	a = (int)luaL_checkinteger(L, 5);


	set_rgba(L, clr_ptr, r, g, b, a);
	return 1;
}

lua_method _call(lua_State *L) {
	int r, g, b, a;

	// essentially flipping the stack around and taking off the library as table 
	// so new doesnt fail
	luaL_checkany(L, 1); // eat library as table
	r = (int)luaL_checkinteger(L, 2); // get r
	g = (int)luaL_checkinteger(L, 3); // get g
	b = (int)luaL_checkinteger(L, 4); // get r
	a = (int)luaL_checkinteger(L, 5); // get g


	lua_pop(L, -1); // empty stack

	lua_pushinteger(L, r);
	lua_pushinteger(L, g);
	lua_pushinteger(L, b);
	lua_pushinteger(L, a);
	return _new(L);
}

lua_method _tostring(lua_State *L) {
	Attr::Color* clr_ptr;

	clr_ptr = check_color(L);
	std::string pt_str = to_string(clr_ptr);
	lua_pushfstring(L, pt_str.c_str(), pt_str.length());
}

}
}

int luaopen_colorlib(lua_State *L) {
	luaL_newmetatable(L, LUA_CLR_META_NAME); /* create metatable for color objects */
	lua_pushvalue(L, -1);  /* duplicate the metatable */
	lua_setfield(L, -2, "__index");  /* mt.__index = mt */
	luaL_setfuncs(L, luaAttrs::color::colorlib_m, 0);  /* register metamethods */

	luaL_newlib(L, luaAttrs::color::colorlib_f);  /* create lib table */
	luaL_newmetatable(L, LUA_CLR_META_LIB_NAME); /* create metatable for THE library */
	luaL_setfuncs(L, luaAttrs::color::colorlib_lm, 0);  /* register library metamethods */
	lua_setmetatable(L, -2); /* set metatable for library */

	return 1;
}