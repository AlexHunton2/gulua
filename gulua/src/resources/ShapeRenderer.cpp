#include "resources/ShapeRenderer.hpp"

using namespace GuluaResources;

ShapeRenderer::ShapeRenderer(Shader &shader) {
	this->mShader = shader;
}

ShapeRenderer::~ShapeRenderer() {
	glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(GL_ARRAY_BUFFER, &mVBO);
}

void TriangleRenderer::drawShape() {
	this->mShader.Use();

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mVertices.size() * sizeof(mVertices[0]), &mVertices[0]);

	glBindVertexArray(this->mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        throw std::runtime_error(
            std::string("TriangleRenderer Draw Shape Failure | GLError: %d", 
            err));
    }
}

void TriangleRenderer::initShape() {
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices[0]), 
        mVertices.data(), GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        throw std::runtime_error(
            std::string("TriangleRenderer Init Shape Failure | GLError: %d", 
            err));
    }
}

void PolygonRenderer::drawShape() {
    this->mShader.Use();

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mVertices.size() * sizeof(mVertices[0]), 
        &mVertices[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 
        mIndicies.size() * sizeof(mIndicies[0]), &mIndicies[0]);

    glBindVertexArray(this->mVAO);
    glDrawElements(GL_TRIANGLES, mIndicies.size(), GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        throw std::runtime_error(
            std::string("PolygonRenderer Draw Shape Failure | GLError: %d", 
            err));
    }
}

void PolygonRenderer::initShape() {
    // Start off by creating our VAO (Vertex Array Object) and binding it
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices[0]), 
        mVertices.data(), GL_STREAM_DRAW);

    glGenBuffers(1, &mIndexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicies.size() * sizeof(mIndicies[0]), 
        mIndicies.data(), GL_STREAM_DRAW);

    // Inform the VAO how to properly index this VBO, ie the size of each data point
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        throw std::runtime_error(
            std::string("PolygonRenderer Init Shape Failure | GLError: %d", 
            err));
    }
}