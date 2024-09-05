#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "resources/Shader.hpp"
#include "resources/ResourceManager.hpp"
#include "resources/FontFace.hpp"
#include "util/util.hpp"

namespace GuluaResources {

class TextRenderer {
public:
	TextRenderer(std::string font, int font_size, std::string text) 
	: mText(text), mFont(font), mFontSize(font_size) {}
	~TextRenderer();
	void initText();
	void drawText();
	std::string mText;
private:
	Shader mShader;
	unsigned int mVAO;
	unsigned int mVBO;
	std::string mFont;
	int mFontSize;
	std::map<char, FontFace::Character> mChars;
};

}

#endif