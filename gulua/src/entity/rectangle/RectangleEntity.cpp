#include "entity/Entity.hpp"

#define PIXEL_TO_GL_X(x) (2.0f*(float)x / mWidth)-1.0f;
#define PIXEL_TO_GL_Y(y) 1.0f-(2.0f*(float)y / mHeight);

void RectangleEntity::init() {
	if (mInitalized) {
		return;
	}

	GuluaResources::Shader shader = GuluaResources::ResourceManager::GetShader("shape");
	if (shader.ID == (unsigned int)-1) {
		shader = GuluaResources::ResourceManager::LoadShader("shaders/shape.vs", "shaders/shape.frag", nullptr, "shape");
	}

	Attr::Point _position = *getPosition();
	Attr::Integer _width = *getWidth();
	Attr::Integer _height = *getHeight();

	std::vector<float> gl_vertices;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			float x = PIXEL_TO_GL_X((_position.x + (float)(i * _width._int)));
			float y = PIXEL_TO_GL_Y((_position.y + (float)(j * _height._int)));

			gl_vertices.push_back(x);
			gl_vertices.push_back(y);
			gl_vertices.push_back(0.0f);
		}
	}

	std::vector<unsigned int> gl_indicies = {0, 1, 2, 1, 2, 3};

	mRenderer = std::make_shared<GuluaResources::PolygonRenderer>(
		shader,
		gl_vertices, 
		gl_indicies, 
		*this->getColor()
	);

	if (mRenderer == nullptr) {
		fprintf(stderr, "Panic! Failed initalize PolygonEntity due to failed shape-renderer\n");
		exit(1);
	}

	mRenderer->initShape();

	mTextRenderer = std::make_shared<GuluaResources::TextRenderer>(
		"../../gulua/fonts/arial.ttf",
		14,
		"(C) Hello World HggH! (test)"
	);

	if (mTextRenderer == nullptr) {
		fprintf(stderr, "Panic! Failed initalize PolygonEntity due to failed text-renderer\n");
	}

	mTextRenderer->initText();

	mInitalized = true;
}

void RectangleEntity::draw() {
	std::vector<float> gl_vertices;
	Attr::Point _position = *getPosition();
	Attr::Integer _width = *getWidth();
	Attr::Integer _height = *getHeight();

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			float x = PIXEL_TO_GL_X((_position.x + (float)(i * _width._int)));
			float y = PIXEL_TO_GL_Y((_position.y + (float)(j * _height._int)));

			gl_vertices.push_back(x);
			gl_vertices.push_back(y);
			gl_vertices.push_back(0.0f);
		}
	}

	mRenderer->mVertices = gl_vertices;
	mRenderer->drawShape();

	mTextRenderer->drawText();
}

std::shared_ptr<Attr::Point> RectangleEntity::getPosition() {
	auto attr_ptr = std::static_pointer_cast<Attr::Point>(mAttrMap["position"]);
	if (attr_ptr == nullptr) {
		// default
		std::shared_ptr<Attr::Point> point = std::make_shared<Attr::Point>();
		setPosition(point);
		return point;
	}
	return attr_ptr;
}

void RectangleEntity::setPosition(std::shared_ptr<Attr::Point> pos) {
	mAttrMap["position"] = pos;
}

std::shared_ptr<Attr::Integer> RectangleEntity::getWidth() {
	auto attr_ptr = std::static_pointer_cast<Attr::Integer>(mAttrMap["width"]);
	if (attr_ptr == nullptr) {
		// default
		std::shared_ptr<Attr::Integer> width = std::make_shared<Attr::Integer>();
		setWidth(width);
		return width;
	}
	return attr_ptr;
}

void RectangleEntity::setWidth(std::shared_ptr<Attr::Integer> width) {
	mAttrMap["width"] = width;
}

std::shared_ptr<Attr::Integer> RectangleEntity::getHeight() {
	auto attr_ptr = std::static_pointer_cast<Attr::Integer>(mAttrMap["height"]);
	if (attr_ptr == nullptr) {
		// default
		std::shared_ptr<Attr::Integer> height = std::make_shared<Attr::Integer>();
		setHeight(height);
		return height;
	}
	return attr_ptr;
}

void RectangleEntity::setHeight(std::shared_ptr<Attr::Integer> height) {
	mAttrMap["height"] = height;
}