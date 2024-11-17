#include "attribute/Attribute.hpp"
#include "entity/LuaEntity.hpp"
#include "lauxlib.h"
#include "lua.h"

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

lua_method generic_get_str(lua_State* L, const char *attr_name) {
    LuaEntity *ent = check_polygon(L);
    std::string id = std::string(ent->id);
    std::string argtype = std::string(luaL_typename(L, 2));

    luaL_argcheck(L, argtype == "string", 2, "must be a string");

    std::shared_ptr<PolygonEntity> polyEnt = std::dynamic_pointer_cast<PolygonEntity>(EntityRegistry::getInstance()->get(id));
    if (polyEnt == nullptr) {
        return 1;
    }

    std::shared_ptr<Attr::String> atr_str = polyEnt->getAttr<Attr::String>(attr_name);

    lua_pushstring(L, atr_str->_str.c_str());
    return 1;
}

lua_method generic_set_str(lua_State* L, const char *attr_name) {
    LuaEntity *ent = check_polygon(L);
    std::string id = std::string(ent->id);
    std::string argtype = std::string(luaL_typename(L, 2));

    std::shared_ptr<PolygonEntity> polyEnt = std::dynamic_pointer_cast<PolygonEntity>(EntityRegistry::getInstance()->get(id));
    if (polyEnt == nullptr) {
        return 1;
    }

    luaL_argcheck(L, argtype == "string", 2, "must be a string");

    const char *text = luaL_checkstring(L, 2);
    std::shared_ptr<Attr::String> atr_str = polyEnt->getAttr<Attr::String>(attr_name);

    atr_str->_str = std::string(text);
    return 0; 
}

lua_method generic_get_int(lua_State* L, const char *attr_name) {
    LuaEntity *ent = _polygon::check_polygon(L);
    std::string id = std::string(ent->id);

    std::shared_ptr<RectangleEntity> rect_ent = std::dynamic_pointer_cast<RectangleEntity>(EntityRegistry::getInstance()->get(id));
    if (rect_ent == nullptr) {
        return 1;
    }
    std::shared_ptr<Attr::Integer> _int = rect_ent->getAttr<Attr::Integer>(attr_name);

    lua_pushinteger(L, +_int->_int);
    return 1;
}

lua_method generic_set_int(lua_State *L, const char* attr_name, int min, int max) {
    LuaEntity *ent = _polygon::check_polygon(L);
    std::string id = std::string(ent->id);

    std::shared_ptr<RectangleEntity> rect_ent = std::dynamic_pointer_cast<RectangleEntity>(EntityRegistry::getInstance()->get(id));

    if (rect_ent == nullptr) {
        return 1;
    }

    int w = luaL_checkinteger(L, 2);
    luaL_argcheck(L, w < max && w > min, 2, "invalid width, outside constraints");

    std::shared_ptr<Attr::Integer> _width = rect_ent->getAttr<Attr::Integer>(attr_name);
    _width->_int = w;
    return 0;
}


lua_method generic_get_color(lua_State *L, const char* attr_name) {
    LuaEntity *ent = check_polygon(L);
    std::string id = std::string(ent->id);

    std::shared_ptr<PolygonEntity> polyEnt = std::dynamic_pointer_cast<PolygonEntity>(EntityRegistry::getInstance()->get(id));
    if (polyEnt == nullptr) {
        return 1;
    }
    std::shared_ptr<Attr::Color> _color = polyEnt->getAttr<Attr::Color>(attr_name);

    luaAttrs::color::push_color(L, _color->r, _color->g, _color->b, _color->a);
    return 1;
}

// set_color(table(r, g, b, a)) or set_color(r, g, b ,a)
lua_method generic_set_color(lua_State *L, const char *attr_name) {
    LuaEntity *ent = check_polygon(L);
    std::string id = std::string(ent->id);
    std::string argtype = std::string(luaL_typename(L, 2));

    std::shared_ptr<PolygonEntity> polyEnt = std::dynamic_pointer_cast<PolygonEntity>(EntityRegistry::getInstance()->get(id));

    if (polyEnt == nullptr) {
        return 1;
    }
    std::shared_ptr<Attr::Color> _color = polyEnt->getAttr<Attr::Color>(attr_name);

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

DEFINE_LUA_ACCESSOR_METHOD(get_color, generic_get_color, "color")
DEFINE_LUA_ACCESSOR_METHOD(set_color, generic_set_color, "color")

DEFINE_LUA_ACCESSOR_METHOD(get_textcolor, generic_get_color, "text-color")
DEFINE_LUA_ACCESSOR_METHOD(set_textcolor, generic_set_color, "text-color")

DEFINE_LUA_ACCESSOR_METHOD(get_text, generic_get_str, "text")
DEFINE_LUA_ACCESSOR_METHOD(set_text, generic_set_str, "text")

}
}
