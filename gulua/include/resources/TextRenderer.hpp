#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "resources/Shader.hpp"
#include "resources/ResourceManager.hpp"
#include "resources/FontFace.hpp"
#include "util/util.hpp"
#include "attribute/Attribute.hpp"

/*
    * Origin for text starts at bottom left:
    * https://learnopengl.com/In-Practice/Text-Rendering
*/

namespace GuluaResources {

class TextRenderer {
public:
   TextRenderer(std::string font, int font_size, std::string text,
                std::shared_ptr<Attr::Color> color, float x = 0, float y = 0)
    : mText(text), mFontSize(font_size), mColor(color), mFont(font), mX(x), mY(y) {}
    ~TextRenderer();
    void initText();
    void drawText();
    void setX(float x) {mX = x;}
    void setY(float y) {mY = y;}
    std::string mText;
    int mFontSize;
    std::shared_ptr<Attr::Color> mColor;
private:
    Shader mShader;
    unsigned int mVAO;
    unsigned int mVBO;
    std::string mFont;
    std::map<char, FontFace::Character> mChars;
    float mX;
    float mY;
};

}

#endif
