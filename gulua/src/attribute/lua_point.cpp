#include "attribute/LuaAttribute.hpp"

namespace luaAttrs {
namespace point {

Attr::Point *check_point(lua_State *L) {
	return check_point(L, 1);
}

Attr::Point *check_point(lua_State *L, int n) {
	void *ud = luaL_checkudata(L, n, LUA_PT_META_NAME);
	luaL_argcheck(L, ud != NULL, 1, "`point' expected");
	return (Attr::Point *)ud;
}

// helper function
static void set_x_y(lua_State *L, Attr::Point *pt_ptr, int x, int y) {
	luaL_argcheck(L, x >= 0 && x <= mWidth, 1, "invalid x size");
	luaL_argcheck(L, y >= 0 && y <= mHeight, 1, "invalid y size");
	pt_ptr->x = x;
	pt_ptr->y = y;
}

Attr::Point *push_point(lua_State *L, int x, int y) {
	Attr::Point *pt_ptr;
	pt_ptr = (Attr::Point *)lua_newuserdata(L, sizeof(Attr::Point));
	luaL_getmetatable(L, LUA_PT_META_NAME);
	lua_setmetatable(L, -2);

	set_x_y(L, pt_ptr, x, y);
	return pt_ptr;
}

std::string to_string(Attr::Attribute *attr) {
	Attr::Point *pt_ptr = static_cast<Attr::Point *>(attr);
	// (x, y)
	return "(" + std::to_string(pt_ptr->x) + ", " + std::to_string(pt_ptr->y) + ")"; 
}

// _new(x, y)
lua_method _new(lua_State *L) {
	int x; // inputs
	int y;
	x = (int)luaL_checkinteger(L, 1);
	y = (int)luaL_checkinteger(L, 2);

	push_point(L, x, y);
	return 1;
}

// point[key] where key is always a string -> return is any
lua_method _index(lua_State *L) {
	Attr::Point *pt;
	std::string key;

	pt = check_point(L);
	key = std::string(luaL_checkstring(L, 2));

	if (key == "x") {
		lua_pushinteger(L, pt->x);
		return 1;
	} else if (key == "y") {
		lua_pushinteger(L, pt->y);
		return 1;
	}

	return 0;
}

lua_method _newindex(lua_State *L) {
	Attr::Point *pt_ptr;
	std::string key;
	int val;

	pt_ptr = check_point(L);
	key = std::string(luaL_checkstring(L, 2));
	val = (int)luaL_checkinteger(L, 3);

	if (key == "x") {
		set_x_y(L, pt_ptr, val, pt_ptr->y);	
	} else if (key == "y") {
		set_x_y(L, pt_ptr, pt_ptr->x, val);	
	}

	return 0;

}

lua_method _set(lua_State *L) {
	Attr::Point *pt_ptr;
	int x;
	int y;

	pt_ptr = check_point(L);
	x = (int)luaL_checkinteger(L, 2);
	y = (int)luaL_checkinteger(L, 3);

	set_x_y(L, pt_ptr, x, y);
	return 1;
}

lua_method _call(lua_State *L) {
	int x;
	int y;

	// essentially flipping the stack around and taking off the library as table 
	// so new doesnt fail
	luaL_checkany(L, 1); // eat library as table
	x = (int)luaL_checkinteger(L, 2); // get x
	y = (int)luaL_checkinteger(L, 3); // get y

	lua_pop(L, -1); // empty stack

	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	return _new(L);
}

lua_method _tostring(lua_State *L) {
	Attr::Point* pt_ptr;

	pt_ptr = check_point(L);
	std::string pt_str = to_string(pt_ptr);
	lua_pushfstring(L, pt_str.c_str(), pt_str.length());
}

}
}

int luaopen_pointlib(lua_State *L) {
	luaL_newmetatable(L, LUA_PT_META_NAME); /* create metatable for point objects */
	lua_pushvalue(L, -1);  /* duplicate the metatable */
	lua_setfield(L, -2, "__index");  /* mt.__index = mt */
	luaL_setfuncs(L, luaAttrs::point::pointlib_m, 0);  /* register metamethods */

	luaL_newlib(L, luaAttrs::point::pointlib_f);  /* create lib table */
	luaL_newmetatable(L, LUA_PT_META_LIB_NAME); /* create metatable for THE library */
	luaL_setfuncs(L, luaAttrs::point::pointlib_lm, 0);  /* register library metamethods */
	lua_setmetatable(L, -2); /* set metatable for library */

	return 1;
}