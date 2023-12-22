#include "luaapi/luaAPI.hpp"

void luaAPI::loadLua(const char *fileName) {
	int error;
	lua_State *luaState = luaL_newstate();
	luaL_openlibs(luaState);

	// requiring gulua libraries
	luaL_requiref(luaState, "entitylib", luaopen_entitylib, 1);
  lua_pop(luaState, 1);  /* remove lib */

	// read in file
	error = luaL_loadfile(luaState, fileName) || lua_pcall(luaState, 0, 0, 0);
    if (error) {
        luaAPI::error(luaState, true, "Lua Error! file: %s\n", 
        	lua_tostring(luaState, -1));
        lua_pop(luaState, 1);
        exit(1);
    }
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

void luaAPI::error(lua_State *L, bool killFlag, const char *fmt, ...) {
	va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    if (killFlag)
    	exit(1);
}

/*
* @param lua_State
* @param func - Name of the global function
* @param sig - Format of the arguments/results 
*	"d - double, i - integer, s - string"
* @param ... - arguments + pointers to return values
* please seperate arguments and return values with a >
* example: "ii>i"
* 
* @note: up to caller to pop results from stack
* 
* @return nothing, but arguments are modified with return values
* see pg. 243 of Lua book
*/
void luaAPI::callGlobalFunction(lua_State *L, const char *func, 
	const char *sig, ...) {
	va_list vl;
	int narg, nres;
	va_start(vl, sig); // args and the last arguement
	lua_getglobal(L, func);

	// push arguments
	for (narg = 0; *sig; narg++) {  /* repeat for each argument */
          /* check stack space */
          luaL_checkstack(L, 1, "too many arguments");
          switch (*sig++) {
            case 'd':  /* double argument */
              lua_pushnumber(L, va_arg(vl, double));
              break;
            case 'i':  /* int argument */
              lua_pushinteger(L, va_arg(vl, int));
              break;
            case 's':  /* string argument */
              lua_pushstring(L, va_arg(vl, char *));
              break;
            case '>':  /* end of arguments */
              goto endargs;  /* break the loop */
            default:
              error(L, false, "invalid option (%c)", *(sig - 1));
          }
	}
	endargs:

	nres = strlen(sig); // number of results

	// do call
	if (lua_pcall(L, narg, nres, 0) != 0) {
		error(L, false, "error calling '%s': %s", func, lua_tostring(L, -1));
    }

    nres = -nres;  /* stack index of first result */
	while (*sig) {  /* repeat for each result */
		switch (*sig++) {
			case 'd': {  /* double result */
				int isnum;
				double n = lua_tonumberx(L, nres, &isnum);
				if (!isnum) {
					error(L, false, "wrong result type");
				}
				*va_arg(vl, double *) = n;
				break;
			}
			case 'i': {  /* int result */
				int isnum;
				int n = lua_tointegerx(L, nres, &isnum);
				if (!isnum) {
					error(L, false, "wrong result type");
				}
				*va_arg(vl, int *) = n;
				break;
			}
			case 's': {  /* string result */
				const char *s = lua_tostring(L, nres);
				if (s == NULL) {
					error(L, false, "wrong result type");
				}
				*va_arg(vl, const char **) = s;
				break;
			}
			default: {
				error(L, false, "invalid option (%c)", *(sig - 1));
			}
		}
		nres++; 
	}

	va_end(vl);
}

std::string luaAPI::retrieveEntIDFromTable(lua_State *L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	
	std::string ent_id;
	// reading table for the ent_id
  lua_pushnil(L);
	while (lua_next(L, 1) != 0) {
		if (lua_type(L, -2) == LUA_TSTRING) { // if key is string
			std::string key = std::string(lua_tostring(L, -2));
			if (key == "ent_id") {
				ent_id = std::string(lua_tostring(L, -1));
			}
		}
		lua_pop(L, 1);
	}
	return ent_id;
}