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
	virtual ~Entity() = default;
protected:
	Entity();
	bool mInitalized = false;
	std::string id;
	std::map<std::string, std::shared_ptr<Attr::Attribute>> mAttrMap;
};

class PolygonEntity : public Entity {
public:
	PolygonEntity(int edges) : Entity(), mEdges(edges), mRenderer(nullptr) {}
	virtual ~PolygonEntity() = default;
	virtual void init() {};
	virtual void draw() {};
	std::shared_ptr<Attr::Color> getColor();
	void setColor(std::shared_ptr<Attr::Color> color);
	int mEdges;
protected:
	std::shared_ptr<GuluaResources::PolygonRenderer> mRenderer;
};

class TriangleEntity : public PolygonEntity  {
public:
	TriangleEntity() : PolygonEntity(3) {}
	~TriangleEntity() {}
	void init() override;
	void draw() override;
	std::shared_ptr<Attr::PointVec> getVertices();
	void setVertices(std::shared_ptr<std::vector<Attr::Point>> vertices);
	const int mEdges = 3;
};

class RectangleEntity : public PolygonEntity {
public:
	RectangleEntity() : PolygonEntity(4) {}
	~RectangleEntity() {}
	void init() override;
	void draw() override;
	std::shared_ptr<Attr::Point> getPosition();
	void setPosition(std::shared_ptr<Attr::Point> pos);
	std::shared_ptr<Attr::Integer> getWidth();
	void setWidth(std::shared_ptr<Attr::Integer> width);
	std::shared_ptr<Attr::Integer> getHeight();
	void setHeight(std::shared_ptr<Attr::Integer> height);
	const int mEdges = 4;
};

#endif