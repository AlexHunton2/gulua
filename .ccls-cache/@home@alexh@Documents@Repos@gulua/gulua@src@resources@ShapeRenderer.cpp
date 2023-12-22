/*******************************************************************
** This code is part of Breakout.
** https://github.com/JoeyDeVries/LearnOpenGL/
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
*/ 
#include "resources/ShapeRenderer.hpp"

using namespace GuluaResources;

ShapeRenderer::ShapeRenderer(Shader &shader) {
	this->mShader = shader;
}

ShapeRenderer::~ShapeRenderer() {
	glDeleteVertexArrays(1, &this->mVAO);
}

void TriangleRenderer::drawShape() {
	this->mShader.Use();

	glBindVertexArray(this->mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void TriangleRenderer::initShape() {
    unsigned int VBO;
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices), &mVertices[0], GL_STATIC_DRAW);

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

    glBindVertexArray(this->mVAO);
    glDrawElements(GL_TRIANGLES, mIndicies.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void PolygonRenderer::initShape() {
    // Start off by creating our VAO (Vertex Array Object) and binding it
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Create our Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Fill it up with all the vertices
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(mVertices), &mVertices[0], GL_STATIC_DRAW);

    // Inform the VAO how to properly index this VBO, ie the size of each data point
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Create our Index Buffer Object, 
    //(the indicies of the triangles that make up a shape)
    // imagine rectangle with veticies 0, 1, 2, 3. Two triangles make up rectangle of 0,1,2 and 2,3,1
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndicies.size() * sizeof(mIndicies), &mIndicies[0], GL_STATIC_DRAW);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}


