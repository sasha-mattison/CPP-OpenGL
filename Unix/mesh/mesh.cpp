#include "mesh.h"
#include <iostream>

Mesh::Mesh(const Vertices& vertices, bool dynamic)
    : vertexCount(vertices.vertexCount()),
      usage(dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW) {

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.data.size() * sizeof(float),
        vertices.data.data(),
        usage
    );

    glVertexAttribPointer(
        0,
        vertices.stride,
        GL_FLOAT,
        GL_FALSE,
        vertices.stride * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

void Mesh::updateVertices(const Vertices& vertices) {
    vertexCount = vertices.vertexCount();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.data.size() * sizeof(float),
        vertices.data.data(),
        usage
    );
}
