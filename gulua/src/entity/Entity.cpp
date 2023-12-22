#include "entity/Entity.hpp"
#include "luaapi/luaAPI.hpp"

Entity::Entity() {}

void TriangleEntity::init() {
	if (mInitalized) {
		return;
	}

	if (mVertices.size() != 3) {
		throw std::runtime_error("Invalid TriangleEntity Vertices");
	}

	GuluaResources::Shader shader = GuluaResources::ResourceManager::GetShader("shape");
	unsigned int unsignedNegOne = -1;
	if (shader.ID == unsignedNegOne) {
		shader = GuluaResources::ResourceManager::LoadShader("shaders/shape.vs", "shaders/shape.frag", nullptr, "shape");
	}


	std::vector<float> vertices;
	for (auto pair : mVertices) {
		float x = (2.0f*(float)pair.first / mWidth)-1.0f;
		float y = 1.0f-(2.0f*(float)pair.second / mHeight);
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);
	}

	mRenderer = std::make_shared<GuluaResources::TriangleRenderer>(shader,vertices);
	mInitalized = true;
}

void TriangleEntity::draw() {
	mRenderer->drawShape();
}

/*
	Methods given to lua
*/
static int get_verticies(lua_State *L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	
	std::string id = luaAPI::retrieveEntIDFromTable(L);
	if (id.empty()) {
		return 1;
	}

	std::shared_ptr<TriangleEntity> triEnt = std::dynamic_pointer_cast<TriangleEntity>(EntityRegistry::getInstance()->get(id));
	if (!triEnt) {
		return 1;
	}

	lua_newtable(L);
	int i = 1;
	for (std::pair<int, int> pair : triEnt->mVertices) {
		lua_pushinteger(L, i);
		lua_pushinteger(L, pair.first);
		lua_settable(L, -3);
		i++;
		lua_pushinteger(L, i);
		lua_pushinteger(L, pair.second);
		lua_settable(L, -3);
		i++;
	}

	return 1;
}

static int set_verticies(lua_State *L) {
	luaL_checktype(L, 1, LUA_TTABLE);
	
	std::string id = luaAPI::retrieveEntIDFromTable(L);
	if (id.empty()) {
		return 1;
	}

	std::shared_ptr<TriangleEntity> triEnt = std::dynamic_pointer_cast<TriangleEntity>(EntityRegistry::getInstance()->get(id));
	if (!triEnt) {
		return 1;
	}

	// check 2nd arg for table
	luaL_checktype(L, 2, LUA_TTABLE);

	// push all vertices in table to stack
	for (int i=1; i < 7; i++) {
		lua_rawgeti(L, 2, i);
	}

	luaAPI::stackDump(L);

	// retrieve all vertices
	// skip table index, (1 = table, 2 = first vertex, .. 7 = last vertex)
	std::vector<std::pair<int, int>> vertices;
	for (int i=3; i < 9; i+= 2) {
		int x = luaL_checknumber(L, i);
		int y = luaL_checknumber(L, i+1);
		vertices.push_back({x, y});
	}

	triEnt->mVertices = vertices;
	return 1;
} 

void TriangleEntity::emit(lua_State *L) {
	lua_createtable(L, 2, 2);

	LUA_TABLE_APPEND_STR_STR(L, "ent_id", this->getID().c_str(), -3);
	LUA_TABLE_APPEND_STR_FUNC(L, "get_verticies", get_verticies, -3);
	LUA_TABLE_APPEND_STR_FUNC(L, "set_verticies", set_verticies, -3);
}