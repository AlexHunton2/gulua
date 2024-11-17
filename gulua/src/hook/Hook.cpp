#include "hook/Hook.hpp"
#include "luaapi/luaAPI.hpp"

void Hook::call(lua_State *L, const char *sig, ...) {
	va_list vl;
	va_start(vl, sig);
	call(L, sig, vl);
	va_end(vl);
}

void Hook::call(lua_State *L, const char *sig, va_list args) {
	lua_rawgeti(L, LUA_REGISTRYINDEX, mLuaRegistryKey);

	int narg;
	for (narg = 0; *sig; narg++) {  /* repeat for each argument */
          /* check stack space */
          luaL_checkstack(L, 1, "too many arguments");
          switch (*sig++) {
            case 'd':  /* double argument */
              lua_pushnumber(L, va_arg(args, double));
              break;
            case 'i':  /* int argument */
              lua_pushinteger(L, va_arg(args, int));
              break;
            case 's':  /* string argument */
              lua_pushstring(L, va_arg(args, char *));
              break;
            default:
              luaAPI::error(L, "invalid option (%c)", *(sig - 1));
          }
	}

	if (lua_pcall(L, narg, 0, 0) != 0) {
		luaAPI::error(L, "error calling hook '%s': %s", 
			mIdentifier.c_str(), lua_tostring(L, -1));
    }
}
