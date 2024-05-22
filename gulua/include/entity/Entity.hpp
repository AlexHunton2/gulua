/*
	Entity.hpp

	Core of entities, intefaces with OpenGL, interfaced with Lua
*/
#ifndef ENTITY
#define ENTITY
#pragma once

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

#include "attribute/Attribute.hpp"

class Entity {
public:
	virtual void init() {} // called once
	virtual void draw() {} // called every frame
	bool isInitalized() { return mInitalized; }
	void setID(std::string id) { this->id = id; }
	std::string getID() { return this->id; }	
	~Entity() {}
protected:
	Entity();
	bool mInitalized = false;
	std::string id;
	std::map<std::string, std::shared_ptr<Attr::Attribute>> mAttrMap;
};

class TriangleEntity : public Entity {
public:
	TriangleEntity() : Entity(), mRenderer(nullptr) {}
	void init();
	void draw();
	std::shared_ptr<Attr::PointVec> getVertices();
	void setVertices(std::shared_ptr<std::vector<Attr::Point>> vertices);
	std::shared_ptr<Attr::Color> getColor();
	void setColor(std::shared_ptr<Attr::Color> color);
private:
	std::shared_ptr<GuluaResources::TriangleRenderer> mRenderer;
};

#endif