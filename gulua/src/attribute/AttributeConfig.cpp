#include "attribute/LuaAttribute.hpp"

std::map<std::string, std::shared_ptr<AttributeType>> attr_type_map = std::map<std::string, std::shared_ptr<AttributeType>>();

int init_attr_type_map() {
	// Register Attribute Types

	// Point
	std::shared_ptr<AttributeType> pt = std::make_shared<AttributeType>();
	pt->luaopen_entlib = luaopen_pointlib;
	attr_type_map.insert({"Point", pt});
}