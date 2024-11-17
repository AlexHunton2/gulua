#include "attribute/Attribute.hpp"
#include "entity/Entity.hpp"
#include "gulua.hpp"

void TriangleEntity::init() {
    if (mInitalized) {
        return;
    }

    PolygonEntity::init();

    // initalize vector
    std::shared_ptr<Attr::PointVec> attr_pvec = getAttr<Attr::PointVec>("vertices");

    std::vector<float> gl_vertices;
    for (auto pair : *attr_pvec->attrs) {
        // TODO : Replace conversion with shader
        float x = (2.0f*(float)pair.x / mWidth)-1.0f;
        float y = 1.0f-(2.0f*(float)pair.y / mHeight);
        gl_vertices.push_back(x);
        gl_vertices.push_back(y);
        gl_vertices.push_back(0.0f);
    }

    mRenderer = std::make_shared<GuluaResources::TriangleRenderer>(
        mShader,
        gl_vertices, 
        this->getAttr<Attr::Color>("color")
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

    std::shared_ptr<Attr::PointVec> attr_pvec = getAttr<Attr::PointVec>("vertices");
    std::shared_ptr<std::vector<Attr::Point>> _vertices = attr_pvec->attrs;
    if (_vertices == nullptr) {
        return;
    }

    for (auto pair : *_vertices) {
        // TODO : Replace conversion with macro
        float x = (2.0f*(float)pair.x / mWidth)-1.0f;
        float y = 1.0f-(2.0f*(float)pair.y / mHeight);
        gl_vertices.push_back(x);
        gl_vertices.push_back(y);
        gl_vertices.push_back(0.0f);
    }

    mRenderer->mVertices = gl_vertices;
    mRenderer->drawShape();

    // set text as center of triangle
    int sum_x = 0, sum_y = 0;
    for (auto pair: (*getAttr<Attr::PointVec>("vertices")->attrs)) {
        sum_x += pair.x;
        sum_y += pair.y;
    }

    mTextRenderer->setX(sum_x / 3);
    mTextRenderer->setY(sum_y / 3);

    mTextRenderer->drawText();
}
