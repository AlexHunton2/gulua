#include "luaapi/luaAPI_hooklib.hpp"

int luaopen_hooklib(lua_State *L) {
	luaL_newlib(L, luaAPI::_hooklib::hooklib);
	return 1;
}

lua_lib_func luaAPI::_hooklib::register_hook(lua_State *L) {
	int arg_size = lua_gettop(L);
	if (arg_size < 3) {
		luaAPI::error(L, "Incorrect Hook Register: wrong argument size.");
		lua_pop(L, 1);
		return 1;
	}
	
	const char *ident = luaL_checkstring(L, 1);
	const char *callsig = luaL_checkstring(L, 2);

	luaL_checktype(L, 3, LUA_TFUNCTION);
	int key = luaL_ref(L, LUA_REGISTRYINDEX); // register function to Lua

	std::shared_ptr<Hook> hook = std::make_shared<Hook>(ident, callsig, key);

	std::shared_ptr<HookRegistry> hook_reg = HookRegistry::getInstance();
	hook_reg->add(hook);
	return 1;
}