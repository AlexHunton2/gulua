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
#include "resources/TextRenderer.hpp"
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
    void init();
    virtual void draw() {};
    template <typename T>
    void setAttr(const char* type, const std::shared_ptr<T>& attr_ptr);
    template <typename T>
    std::shared_ptr<T> getAttr(const char* type);
    int mEdges;
protected:
    std::shared_ptr<GuluaResources::PolygonRenderer> mRenderer;
    GuluaResources::Shader mShader;
    std::shared_ptr<GuluaResources::TextRenderer> mTextRenderer;
};

// Needs to be here cause the templates, compiler doesn't know its
// declared and needs to see it.
template <typename T>
std::shared_ptr<T> PolygonEntity::getAttr(const char* type) {
    auto attr_ptr = std::static_pointer_cast<T>(mAttrMap[type]);
    if (attr_ptr == nullptr) {
        // default
        std::shared_ptr<T> attr_ptr = std::make_shared<T>();
        setAttr(type, attr_ptr);
        return attr_ptr;
    }
    return attr_ptr;
}

template <typename T>
void PolygonEntity::setAttr(const char* type, const std::shared_ptr<T>& attr_ptr) {
    mAttrMap[type] = attr_ptr;
}

class TriangleEntity : public PolygonEntity  {
public:
    TriangleEntity() : PolygonEntity(3) {}
    ~TriangleEntity() {}
    void init() override;
    void draw() override;
    const int mEdges = 3;
};

class RectangleEntity : public PolygonEntity {
public:
    RectangleEntity() : PolygonEntity(4) {}
    ~RectangleEntity() {}
    void init() override;
    void draw() override;
    const int mEdges = 4;
};

#endif
