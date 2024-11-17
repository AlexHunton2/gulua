#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include "attribute/Attribute.hpp"
#include "resources/Shader.hpp"

#include "util/util.hpp"

namespace GuluaResources {

class ShapeRenderer {
public:
    ~ShapeRenderer();
    virtual void drawShape() {}
    Shader mShader;
protected:
    ShapeRenderer(Shader &shader);
    virtual void initShape() {}
    unsigned int mVAO;
    unsigned int mVBO;
};

class PolygonRenderer : public ShapeRenderer {
public:
    PolygonRenderer(Shader &shader, std::vector<float> vertices, std::vector<unsigned int> indicies, const std::shared_ptr<Attr::Color>& color) : 
    ShapeRenderer(shader), mVertices(vertices), mColor(color), mIndicies(indicies) {}
    virtual void drawShape();
    virtual void initShape();
    std::vector<float> mVertices;
    std::shared_ptr<Attr::Color> mColor;
protected:
    std::vector<unsigned int> mIndicies;
    unsigned int mIndexBufferId;
};

class TriangleRenderer : public PolygonRenderer {
public:
    TriangleRenderer(Shader &shader, std::vector<float> vertices, const std::shared_ptr<Attr::Color>& color) : 
    PolygonRenderer(shader, vertices, std::vector<unsigned int>(), color)  {}
    void drawShape() override;
    void initShape() override;
protected:
private:
    const std::vector<unsigned int> mIndicies = std::vector<unsigned int>();
    const unsigned int mIndexBufferId = -1;
};

} // end of GuluaResources


#endif
