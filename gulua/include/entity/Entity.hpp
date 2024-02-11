#ifndef ENTITY
#define ENTITY

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "resources/ShapeRenderer.hpp"
#include "resources/ResourceManager.hpp"
#include "resources/Shader.hpp"
#include <vector>
#include "gulua.hpp"
#include <memory>

class Entity {
public:
	virtual void init() {} // called once
	virtual void draw() {} // called every frame
	virtual void emit(lua_State *L) {} // pushes a table representing the object to lua stack 
	bool isInitalized() { return mInitalized; }
	void setID(std::string id) { this->id = id; }
	std::string getID() { return this->id; }	
	~Entity() {}
protected:
	Entity();
	bool mInitalized = false;
	std::string id;
};

class TriangleEntity : public Entity {
public:
	TriangleEntity(std::vector<std::pair<int, int>> vertices) : Entity(), mVertices(vertices), mRenderer(nullptr) {}
	void init();
	void draw();
	void emit(lua_State *L);
	std::vector<std::pair<int, int>> mVertices;
private:
	std::shared_ptr<GuluaResources::TriangleRenderer> mRenderer;
};

#endif