#include "entity/Entity.hpp"

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
	std::vector<float> vertices;
	for (auto pair : mVertices) {
		float x = (2.0f*(float)pair.first / mWidth)-1.0f;
		float y = 1.0f-(2.0f*(float)pair.second / mHeight);
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f);
	}

	mRenderer->mVertices = vertices;
	mRenderer->drawShape();
}