#include "attribute/Attribute.hpp"
#include "entity/LuaEntity.hpp"

namespace luaEnts {
namespace _triangle {

int _create(lua_State *L) {
    // create TriangleEntity
    std::shared_ptr<TriangleEntity> tri_ent = std::make_shared<TriangleEntity>();
    if (tri_ent == nullptr) {
        luaL_error(L, "failed to create 'Triangle'");
    }

    // Register TriangleEntity
    std::shared_ptr<EntityRegistry> ent_reg = EntityRegistry::getInstance();
    std::string tri_id = ent_reg->add(tri_ent);
    if (tri_ent == NULL) {
        luaL_error(L, "failed to create 'Triangle'");
    }

    // Update Lua Entity
    LuaEntity *lua_ent = (LuaEntity *)lua_newuserdata(L, sizeof(LuaEntity));
    luaL_getmetatable(L, "Gulua.Triangle");
      lua_setmetatable(L, -2);

    strncpy(lua_ent->id, tri_id.c_str(), ENT_STR_SIZE-1);

    const char* triangle_type_name = "Triangle";
    strncpy(lua_ent->type, triangle_type_name, ENT_STR_SIZE-1);

    return 1;
}

lua_method get_vertices(lua_State *L) {
    LuaEntity *ent = _polygon::check_polygon(L);
    std::string id = std::string(ent->id);

    std::shared_ptr<TriangleEntity> tri_ent = std::dynamic_pointer_cast<TriangleEntity>(EntityRegistry::getInstance()->get(id));
    if (tri_ent == nullptr) {
        return 1;
    }
    std::shared_ptr<std::vector<Attr::Point>> _vertices = (tri_ent->getAttr<Attr::PointVec>("vertices")->attrs);


    lua_newtable(L);
    int i = 1;
    for (auto pair : *_vertices) {
        lua_pushinteger(L, i);
        luaAttrs::point::push_point(L, pair.x, pair.y);
        lua_settable(L, -3);
        i++;
    }

    return 1;
}

lua_method set_vertices(lua_State *L) {
    LuaEntity *ent = _polygon::check_polygon(L);
    std::string id = std::string(ent->id);
    std::string argtype = std::string(luaL_typename(L, 2));

    std::shared_ptr<TriangleEntity> tri_ent = std::dynamic_pointer_cast<TriangleEntity>(EntityRegistry::getInstance()->get(id));

    if (tri_ent == nullptr) {
        return 1;
    }

    tri_ent->init();

    std::shared_ptr<Attr::PointVec> attr_pvec = tri_ent->getAttr<Attr::PointVec>("vertices");
    std::shared_ptr<std::vector<Attr::Point>> _vertices = attr_pvec->attrs;
    if (_vertices == nullptr) {
        return 1;
    }

    luaL_argcheck(L, argtype == "table" || argtype == "userdata", 2, "not point ot table");

    int i;
    if (argtype == "table") {
        for (i = 0; i < tri_ent->mEdges; i++) {
            lua_rawgeti(L, 2, i+1); // push all points
        }
    }

    int j = argtype == "table" ? 1 : 0;
    Attr::Point *pt_ptr;
    _vertices->clear();
    for (int i = 0; i < tri_ent->mEdges; i++) {
        pt_ptr = luaAttrs::point::check_point(L, i+2+j);
        _vertices->push_back(*pt_ptr);
    }
    return 0;
}

}
}

int luaopen_trianglelib(lua_State *L) {
    luaL_newmetatable(L, "Gulua.Triangle");

    lua_pushvalue(L, -1);  /* duplicate the metatable */
    lua_setfield(L, -2, "__index");  /* mt.__index = mt */
    luaL_setfuncs(L, luaEnts::_triangle::trianglelib_m, 0);  /* register metamethods */
    luaL_newlib(L, luaEnts::_triangle::trianglelib_m);  /* create lib table */

    return 1;
}
