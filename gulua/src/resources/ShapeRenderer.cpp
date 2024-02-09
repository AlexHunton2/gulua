#include "resources/ShapeRenderer.hpp"

using namespace GuluaResources;

ShapeRenderer::ShapeRenderer(Shader &shader) {
	this->mShader = shader;
}

ShapeRenderer::~ShapeRenderer() {
    printf("Error: %d \n", glGetError());

	glDeleteVertexArrays(1, &mVAO);
    glDeleteBuffers(GL_ARRAY_BUFFER, &mVBO);
}

void TriangleRenderer::drawShape() {
	this->mShader.Use();

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, mVertices.size() * sizeof(mVertices), &mVertices[0]);

	glBindVertexArray(this->mVAO);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TriangleRenderer::initShape() {
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices[0]), mVertices.data(), GL_STREAM_DRAW);

    glBindVertexArray(mVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}

void PolygonRenderer::drawShape() {
    this->mShader.Use();

    // todo this won't work cause the buffers aren't updated tehehe :3

    glBindVertexArray(this->mVAO);
    glDrawElements(GL_TRIANGLES, mIndicies.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void PolygonRenderer::initShape() {
    // Start off by creating our VAO (Vertex Array Object) and binding it
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Create our Vertex Buffer Object
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    // Fill it up with all the vertices
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices), &mVertices[0], GL_STREAM_DRAW);

    // Inform the VAO how to properly index this VBO, ie the size of each data point
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Create our Index Buffer Object, 
    //(the indicies of the triangles that make up a shape)
    // imagine rectangle with veticies 0, 1, 2, 3. Two triangles make up rectangle of 0,1,2 and 2,3,1
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicies.size() * sizeof(mIndicies), &mIndicies[0], GL_STREAM_DRAW);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}