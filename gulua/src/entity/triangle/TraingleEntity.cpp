#include "entity/Entity.hpp"

void TriangleEntity::init() {
	if (mInitalized) {
		return;
	}

	std::vector<Attr::Point> _vertices = (*getVertices()->attrs);
	if ((int)_vertices.size() != mEdges) {
		throw std::runtime_error("Invalid Vertices");
	}

	GuluaResources::Shader shader = GuluaResources::ResourceManager::GetShader("shape");
	unsigned int unsignedNegOne = -1;
	if (shader.ID == unsignedNegOne) {
		shader = GuluaResources::ResourceManager::LoadShader("shaders/shape.vs", "shaders/shape.frag", nullptr, "shape");
	}

	std::vector<float> gl_vertices;
	for (auto pair : _vertices) {
		// TODO : Replace conversion with macro
		float x = (2.0f*(float)pair.x / mWidth)-1.0f;
		float y = 1.0f-(2.0f*(float)pair.y / mHeight);
		gl_vertices.push_back(x);
		gl_vertices.push_back(y);
		gl_vertices.push_back(0.0f);
	}

	mRenderer = std::make_shared<GuluaResources::TriangleRenderer>(
		shader,
		gl_vertices, 
		*this->getColor()
	);
	if (mRenderer == nullptr) {
		fprintf(stderr, "Panic! Failed initalize TriangleEntity due to failed renderer\n");
		exit(1);
	}

	mRenderer->initShape();

	mInitalized = true;
}

void TriangleEntity::draw() {
	std::vector<float> gl_vertices;
	for (auto pair : (*getVertices()->attrs)) {
		// TODO : Replace conversion with macro
		float x = (2.0f*(float)pair.x / mWidth)-1.0f;
		float y = 1.0f-(2.0f*(float)pair.y / mHeight);
		gl_vertices.push_back(x);
		gl_vertices.push_back(y);
		gl_vertices.push_back(0.0f);
	}

	mRenderer->mVertices = gl_vertices;
	mRenderer->drawShape();
}

std::shared_ptr<Attr::PointVec> TriangleEntity::getVertices() {
	auto attr_ptr = std::static_pointer_cast<Attr::PointVec>(mAttrMap["vertices"]);
	if (attr_ptr == nullptr) {
		// default
		std::shared_ptr<std::vector<Attr::Point>> vertices = std::make_shared<std::vector<Attr::Point>>();
		for (int i=0; i < mEdges; i++) {
			Attr::Point pt;
			vertices->push_back(pt);
		}
		setVertices(vertices);
		return getVertices();
	}
	return attr_ptr;
}

void TriangleEntity::setVertices(std::shared_ptr<std::vector<Attr::Point>> vertices) {
	std::shared_ptr<Attr::PointVec> pt_vec = std::make_shared<Attr::PointVec>();
	pt_vec->attrs = vertices;
	mAttrMap["vertices"] = pt_vec;
}