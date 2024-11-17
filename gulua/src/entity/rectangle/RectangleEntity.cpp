#include "entity/Entity.hpp"

#define PIXEL_TO_GL_X(x) (2.0f*(float)x / mWidth)-1.0f;
#define PIXEL_TO_GL_Y(y) 1.0f-(2.0f*(float)y / mHeight);

void RectangleEntity::init() {
    if (mInitalized) {
        return;
    }

    PolygonEntity::init();

    Attr::Point _position = *getAttr<Attr::Point>("position");
    Attr::Integer _width = *getAttr<Attr::Integer>("width");
    Attr::Integer _height = *getAttr<Attr::Integer>("height");

    // TODO: fix the conversion for draw/init, shaders are your
    // friends here
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
        mShader,
        gl_vertices, 
        gl_indicies, 
        this->getAttr<Attr::Color>("color")
    );

    if (mRenderer == nullptr) {
        fprintf(stderr, "Panic! Failed initalize PolygonEntity due to failed shape-renderer\n");
        exit(1);
    }

    mRenderer->initShape();
 
    mInitalized = true;
}

void RectangleEntity::draw() {
    if (!mInitalized) {
        return;
    }

    std::vector<float> gl_vertices;
    Attr::Point _position = *getAttr<Attr::Point>("position");
    Attr::Integer _width = *getAttr<Attr::Integer>("width");
    Attr::Integer _height = *getAttr<Attr::Integer>("height");

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

    mTextRenderer->setX((_width._int / 2) + _position.x);
    mTextRenderer->setY((_height._int / 2) + _position.y +
                        (0.4 * mTextRenderer->mFontSize));
    // 0.4 * mTextRender->mFontSize will center on the vertical, roughly
    // bearingY = 0.4 * font size

    mTextRenderer->drawText();
}
