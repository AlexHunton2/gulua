#include "resources/TextRenderer.hpp"

// fix this:
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

using namespace GuluaResources;

TextRenderer::~TextRenderer() {
	glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(GL_ARRAY_BUFFER, &mVBO);
};

void TextRenderer::initText() {
	GLenum err;

    glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 

	// get (or load) the shader
	mShader = ResourceManager::GetShader("text");
	if (mShader.ID == (unsigned int)-1) {
		mShader = ResourceManager::LoadShader("shaders/text.vs", "shaders/text.frag", nullptr, "text");
	}
	
	// projection for (world -> pixel)
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCREEN_WIDTH), static_cast<float>(SCREEN_HEIGHT), 0.0f);
	mShader.Use();
	glUniformMatrix4fv(glGetUniformLocation(mShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	FontFace font_face = FontFace(mFont, mFontSize);
	if (font_face.init() == -1) {
		throw std::runtime_error(
			util_format("TextRenderer Initialize Shape Failure | Failed to load font face")
		);
	};
	mChars = font_face.mChars;

	// create buffer / array objects
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

	err = glGetError();
	if (err != GL_NO_ERROR) {
		throw std::runtime_error(
			util_format("TextRenderer Initialize Shape Failure | GLError: %d", err)
		);
	}
}

void TextRenderer::drawText() {
	GLenum err;
	// TODO: add color

	// activate corresponding render state
	mShader.Use();
	mShader.SetVector3f("textColor", 0.5, 0.8f, 0.2f);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(mVAO);

	float scale = 1.0f;

	// TOODO: fix
	float x = 20.0f;
	float y = 500.0f;

	// iterate through all characters
    std::string::const_iterator c;
    for (c = mText.begin(); c != mText.end(); c++) {
        FontFace::Character ch = mChars[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - ch.bearing.y * scale;

        float w = ch.size.x * scale;
        float h = ch.size.y * scale;

		GLfloat vertices[6][4] = {
		    { xpos,     ypos + h,	0.0f, 1.0f },
		    { xpos,     ypos,       0.0f, 0.0f },
		    { xpos + w, ypos,       1.0f, 0.0f },

		    { xpos,     ypos + h, 	0.0f, 1.0f },
		    { xpos + w, ypos,      	1.0f, 0.0f },
		    { xpos + w, ypos + h, 	1.0f, 1.0f }
		};
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

	err = glGetError();
	if (err != GL_NO_ERROR) {
		throw std::runtime_error(
			util_format("TextRenderer Draw Shape Failure | GLError: %d", err)
		);
	}
}