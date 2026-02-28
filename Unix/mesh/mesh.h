#pragma once
#include <glad/glad.h>
#include "vertices.h"

class Mesh {
public:
    Mesh(const Vertices& vertices, bool dynamic = false);
    ~Mesh();

    void draw() const;

    void updateVertices(const Vertices& vertices);

private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    size_t vertexCount = 0;
    GLenum usage;
};
