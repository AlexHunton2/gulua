#ifndef SHAPE_RENDERER_H
#define SHAPE_RENDERER_H

#include "resources/Shader.hpp"
#include <vector>

namespace GuluaResources {

class ShapeRenderer {
public:
	~ShapeRenderer();
	virtual void drawShape() {}
protected:
	ShapeRenderer(Shader &shader);
	virtual void initShape() {}
	Shader mShader; 
    unsigned int mVAO;
    unsigned int mVBO;
};

class TriangleRenderer : public ShapeRenderer {
public:
	TriangleRenderer(Shader &shader, std::vector<float> vertices) : 
	ShapeRenderer(shader), mVertices(vertices) {
		this->initShape();
	}
	void drawShape();
	std::vector<float> mVertices;
protected:
	void initShape();
};

class PolygonRenderer : public ShapeRenderer {
public:
	PolygonRenderer(Shader &shader, std::vector<float> vertices, std::vector<unsigned int> indicies) : 
	ShapeRenderer(shader), mVertices(vertices), mIndicies(indicies) {
		this->initShape();
	}
	void drawShape();
protected:
	void initShape();
private:
	std::vector<float> mVertices;
	std::vector<unsigned int> mIndicies;
};



} // end of GuluaResources


#endif