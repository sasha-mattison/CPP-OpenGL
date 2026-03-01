// Graphics
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Other
#include <iostream>

// Pipeline
#include "../shaders/shader.h"
#include "../mesh/mesh.h"
#include "../mesh/vertices.h"
#include "../window/window.h"


Mesh createTriangle(float bleft, float tright, int mult , int type) {

    if (type == 1) {
        std::vector<float> vertices = {
            mult*bleft, mult*tright, 0.0f,
            mult*bleft, mult*-tright, 0.0f,
            mult*-bleft, mult*tright, 0.0f};
        Vertices verts(3);
        verts.data = vertices;
        Mesh triangle(verts, true);
        return triangle;
    }
    else if (type == 2) {
        std::vector<float> vertices = {
            mult*bleft, (mult*tright)/2, 0.0f,
            mult*bleft, (mult*tright)/2, 0.0f,
            mult*-bleft, (mult*tright)/2, 0.0f};
        Vertices verts(3);
        verts.data = vertices;
        Mesh triangle(verts, true);
        return triangle;

    }
    else {
        throw std::runtime_error("Invalid triangle type");
    };
}


int main() {
    std::cout << "Program Started" << std::endl << std::endl;

    Window window(800, 600, "OpenGL Window");

    if (!window.get()) {
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    std::vector<float> vertexData = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };

    std::vector<float> vertexData2 = {
        -0.5f, -0.5f, 0.0f,
         -0.5f, 0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };

    Vertices verts(3);
    verts.data = vertexData;

    Vertices verts2(3);
    verts2.data = vertexData2;

    Mesh triangle(verts, true);

    Mesh triangle2(verts2, true);

    Mesh test = createTriangle(-0.5f, 0.5f, 1, 2);

    Shader shader(
        "shaders/vertex_core.glsl",
        "shaders/fragment_core.glsl"
    );

    // Render Loop
    while (!window.shouldClose()) {
        window.processInput();

        glClearColor(0.0f, 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        //triangle.draw();
        //triangle2.draw();
        test.draw();

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}