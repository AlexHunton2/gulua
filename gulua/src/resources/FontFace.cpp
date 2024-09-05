#include "resources/FontFace.hpp"

namespace GuluaResources {

FT_Library FontFace::ft_lib;

int FontFace::loadLibrary() {
	if (FT_Init_FreeType(&FontFace::ft_lib)) {
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}
	return 1;
}

int FontFace::loadFace() {
	if (FT_New_Face(FontFace::ft_lib, mFontFileName.c_str(), 0, &mFtFace)) {
	    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;  
	    return -1;
	}
	return 1;
}

int FontFace::init() {
	if (loadLibrary() == -1) {
		return -1;
	}

	if (loadFace() == -1) {
		return -1;
	}

	FT_Set_Pixel_Sizes(mFtFace, 0, mFontSize);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
  
	for (unsigned char c = 0; c < 128; c++) {
		// load character glyph 
		if (FT_Load_Char(mFtFace, c, FT_LOAD_RENDER)) {
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			mFtFace->glyph->bitmap.width,
			mFtFace->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			mFtFace->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		// now store character for later use
		Character character = {
			texture, 
			glm::ivec2(mFtFace->glyph->bitmap.width, mFtFace->glyph->bitmap.rows),
			glm::ivec2(mFtFace->glyph->bitmap_left, mFtFace->glyph->bitmap_top),
			static_cast<unsigned int>(mFtFace->glyph->advance.x)
		};
		mChars.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(mFtFace);
	FT_Done_FreeType(FontFace::ft_lib);
}

}