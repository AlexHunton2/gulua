// https://learnopengl.com/In-Practice/Text-Rendering

#ifndef FONT_FACE_H
#define FONT_FACE_H

#include "freetype/freetype.h"
#include FT_FREETYPE_H

#include "glm/gtx/hash.hpp"
#include "glm/fwd.hpp"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include <map>
#include <string>
#include <iostream>

namespace GuluaResources {

class FontFace {

public:
struct Character {
    unsigned int textureID;  // ID handle of the glyph texture
    glm::ivec2 size;       // Size of glyph
    glm::ivec2 bearing;    // Offset from baseline to left/top of glyph
    unsigned int advance;    // Offset to advance to next glyph
};
private:
	FT_Face mFtFace;
	std::string mFontFileName;

	int loadLibrary();
	int loadFace();
public:
	static FT_Library ft_lib;
	int mFontSize;
	std::map<char, Character> mChars;
	FontFace(std::string fontFile, int fontSize) : mFontFileName(fontFile), mFontSize(fontSize) {}
	int init();
};

}

#endif