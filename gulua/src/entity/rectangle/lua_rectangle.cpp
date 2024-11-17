#include "attribute/Attribute.hpp"
#include "entity/LuaEntity.hpp"

namespace luaEnts {
namespace _rectangle {

int _create(lua_State *L) {
    // create RectangleEntity
    std::shared_ptr<RectangleEntity> rect_ent = std::make_shared<RectangleEntity>();
    if (rect_ent == nullptr) {
        luaL_error(L, "failed to create 'Rectangle'");
    }

    // Register RectangleEntity
    std::shared_ptr<EntityRegistry> ent_reg = EntityRegistry::getInstance();
    std::string rect_id = ent_reg->add(rect_ent);
    if (rect_ent == NULL) {
        luaL_error(L, "failed to create 'Rectangle'");
    }

    // Update Lua Entity
    LuaEntity *lua_ent = (LuaEntity *)lua_newuserdata(L, sizeof(LuaEntity));
    luaL_getmetatable(L, "Gulua.Rectangle");
      lua_setmetatable(L, -2);

    strncpy(lua_ent->id, rect_id.c_str(), ENT_STR_SIZE-1);

    const char* rectangle_type_name = "Rectangle";
    strncpy(lua_ent->type, rectangle_type_name, ENT_STR_SIZE-1);

    return 1;
}

lua_method get_position(lua_State *L) {
    LuaEntity *ent = _polygon::check_polygon(L);
    std::string id = std::string(ent->id);

    std::shared_ptr<RectangleEntity> rect_ent = std::dynamic_pointer_cast<RectangleEntity>(EntityRegistry::getInstance()->get(id));
    if (rect_ent == nullptr) {
        return 1;
    }
    std::shared_ptr<Attr::Point> _position = rect_ent->getAttr<Attr::Point>("position");


    luaAttrs::point::push_point(L, _position->x, _position->y);
    return 1;
}

lua_method set_position(lua_State *L) {
    LuaEntity *ent = _polygon::check_polygon(L);
    std::string id = std::string(ent->id);
    std::string argtype = std::string(luaL_typename(L, 2));

    std::shared_ptr<RectangleEntity> rect_ent = std::dynamic_pointer_cast<RectangleEntity>(EntityRegistry::getInstance()->get(id));

    if (rect_ent == nullptr) {
        return 1;
    }

    std::shared_ptr<Attr::Point> _position = rect_ent->getAttr<Attr::Point>("position");

    luaL_argcheck(L, argtype == "userdata", 2, "set_position() : not point");
    
    Attr::Point *pt_ptr;
    pt_ptr = luaAttrs::point::check_point(L, 2);

    _position->x = pt_ptr->x;
    _position->y = pt_ptr->y;
    return 0;
}

lua_method get_width(lua_State *L) {
    return _polygon::generic_get_int(L, "width"); 
}

lua_method set_width(lua_State *L) {
    return _polygon::generic_set_int(L, "width", 0, mWidth);
}

lua_method get_height(lua_State *L) {
    return _polygon::generic_get_int(L, "height");
}

lua_method set_height(lua_State *L) {
    return _polygon::generic_set_int(L, "height", 0, mHeight);
}

}
}

int luaopen_rectanglelib(lua_State *L) {
    luaL_newmetatable(L, "Gulua.Rectangle");

    lua_pushvalue(L, -1);  /* duplicate the metatable */
    lua_setfield(L, -2, "__index");  /* mt.__index = mt */
    luaL_setfuncs(L, luaEnts::_rectangle::rectanglelib_m, 0);  /* register metamethods */
    luaL_newlib(L, luaEnts::_rectangle::rectanglelib_m);  /* create lib table */

    return 1;
}
