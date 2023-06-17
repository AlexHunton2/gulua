#include "luaAPI.hpp"

void luaAPI::loadLua(const char *fileName) {
	int error;
	lua_State *luaState = luaL_newstate();
	luaL_openlibs(luaState);

	// read in file
	error = luaL_loadfile(luaState, fileName) || lua_pcall(luaState, 0, 0, 0);
    if (error) {
        luaAPI::error(luaState, "Lua Error! file: %s\n", lua_tostring(luaState, -1));
        //lua_pop(luaState, 1);
        exit(1);
    }

    lua_getglobal(luaState, "Test");

   	if (lua_pcall(luaState, 0, 1, 0) != LUA_OK) {
   		luaAPI::error(luaState, "error running function 'f': %s", lua_tostring(luaState, -1));
   	}

   	int isnum;
   	int z = lua_tonumberx(luaState, -1, &isnum);
   	lua_pop(luaState, 1);
   	printf("Result of Test: %d\n", z);

	luaAPI::stackDump(luaState);

	lua_close(luaState);
}


void luaAPI::stackDump(lua_State *L) {
	int i;
	int top = lua_gettop(L);  /* depth of the stack */
	printf("... Dumping lua stack of size: %d: ...\n", top);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {
			case LUA_TSTRING: {  /* strings */
				printf("'%s'", lua_tostring(L, i));
				break;
			}
			case LUA_TBOOLEAN: {  /* Booleans */
				printf(lua_toboolean(L, i) ? "true" : "false");
				break; 
			}
			case LUA_TNUMBER: {  /* numbers */
				printf("%g", lua_tonumber(L, i));
				break;
			}
			default: {  /* other values */
				printf("%s", lua_typename(L, t));
				break; }
			}
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

void luaAPI::error(lua_State *L, const char *fmt, ...) {
	va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(1);
}