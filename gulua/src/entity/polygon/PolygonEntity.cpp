#include "entity/Entity.hpp"

void PolygonEntity::init() {
    if (mInitalized) {
        return;
    }

    mShader = GuluaResources::ResourceManager::GetShader("shape");
    if (mShader.ID == (unsigned int)-1) {
        mShader = GuluaResources::ResourceManager::LoadShader("shaders/shape.vs", "shaders/shape.frag", nullptr, "shape");
    }

    mTextRenderer = std::make_shared<GuluaResources::TextRenderer>(
        "../../gulua/fonts/arial.ttf",
        50,
        getAttr<Attr::String>("text")->_str.c_str(),
        getAttr<Attr::Color>("text-color")
    );

    if (mTextRenderer == nullptr) {
        fprintf(stderr, "Panic! Failed initalize PolygonEntity due to failed text-renderer\n");
        mInitalized = false;
        return;
    }

    mTextRenderer->initText();
}
