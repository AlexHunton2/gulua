#include "luaapi/luaAPI.hpp"

lua_State* luaAPI::loadLua(const char *fileName) {
    int error;
    lua_State *luaState = luaL_newstate();
    luaL_openlibs(luaState);

    // requiring gulua libraries
    luaL_requiref(luaState, "entitylib", luaopen_entitylib, 1);
  lua_pop(luaState, 1);  /* remove lib */

  luaL_requiref(luaState, "hooklib", luaopen_hooklib, 1);
  lua_pop(luaState, 1);  /* remove lib */

  // Expose Attribute's API
  if (init_attr_type_map() != GULUA_OK) {
       fprintf(stderr, "Failed to Create Attribute Type Map");
  }
  for (auto const&atrr_pair : attr_type_map) {
      std::string id = atrr_pair.first;
      //util_lowercase(&id);
      luaL_requiref(luaState, id.c_str(), atrr_pair.second->luaopen_entlib, 1);
  }

  // Expose Entity's API
  if (init_ent_type_map() != GULUA_OK) {
       fprintf(stderr, "Failed to Create Entity Type Map");
  }
  for (auto const&ent_pair : ent_type_map) {
      std::string id = ent_pair.first;
      util_lowercase(&id);
      luaL_requiref(luaState, id.c_str(), ent_pair.second->luaopen_entlib, 1);
  }

  // Run the autorun file for gulua's lua library
  error = luaL_loadfile(luaState, "../../gulua/lualib/autorun.lua") || lua_pcall(luaState, 0, 0, 0);
  if (error) {
      luaAPI::error(luaState, lua_tostring(luaState, -1));
  }

    // read in file
    error = luaL_loadfile(luaState, fileName) || lua_pcall(luaState, 0, 0, 0);
  if (error) {
      luaAPI::error(luaState, lua_tostring(luaState, -1));
  }
  return luaState;
}

void luaAPI::closeLua(lua_State *L) {
    lua_close(L);
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
    fprintf(stderr, "Lua Error! ");
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "\n");
    va_end(argp);
    lua_pop(L, 1);
    exit(1);
}

/*
* @param lua_State
* @param func - Name of the global function
* @param sig - Format of the arguments/results 
*    "d - double, i - integer, s - string"
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
              error(L, "invalid option (%c)", *(sig - 1));
          }
    }
    endargs:

    nres = strlen(sig); // number of results

    // do call
    if (lua_pcall(L, narg, nres, 0) != 0) {
        error(L, "error calling '%s': %s", func, lua_tostring(L, -1));
    }

    nres = -nres;  /* stack index of first result */
    while (*sig) {  /* repeat for each result */
        switch (*sig++) {
            case 'd': {  /* double result */
                int isnum;
                double n = lua_tonumberx(L, nres, &isnum);
                if (!isnum) {
                    error(L, "wrong result type");
                }
                *va_arg(vl, double *) = n;
                break;
            }
            case 'i': {  /* int result */
                int isnum;
                int n = lua_tointegerx(L, nres, &isnum);
                if (!isnum) {
                    error(L, "wrong result type");
                }
                *va_arg(vl, int *) = n;
                break;
            }
            case 's': {  /* string result */
                const char *s = lua_tostring(L, nres);
                if (s == NULL) {
                    error(L, "wrong result type");
                }
                *va_arg(vl, const char **) = s;
                break;
            }
            default: {
                error(L, "invalid option (%c)", *(sig - 1));
            }
        }
        nres++; 
    }

    va_end(vl);
}
