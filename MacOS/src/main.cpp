// OpenGL + Graphics Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Math
#include <glm/glm.hpp>

// Other Libraries
#include <iostream>
#include <vector>

// Engine
#include "../shaders/shader.h"

int windowWidth = 800;
int windowHeight = 600;

bool fullscreen = false;
int windowedWidth = 800, windowedHeight = 600;
int windowedX = 100, windowedY = 100;

void toggleFullscreen(GLFWwindow* window) {
    fullscreen = !fullscreen;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    if (fullscreen) {
        glfwGetWindowPos(window, &windowedX, &windowedY);
        glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

        glfwSetWindowMonitor(
            window,
            monitor,
            0, 0,
            mode->width,
            mode->height,
            mode->refreshRate
        );
    } else {
        glfwSetWindowMonitor(
            window,
            nullptr,
            windowedX,
            windowedY,
            windowedWidth,
            windowedHeight,
            0
        );
    }
}

void processInput(GLFWwindow* window) {
    static bool fPressedLastFrame = false;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    bool fPressed = glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS;
    if (fPressed && !fPressedLastFrame) {
        toggleFullscreen(window);
    }

    fPressedLastFrame = fPressed;
}

int main() {
    std::cout << "Program Started" << std::endl << std::endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL Window", nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0
    );
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Shader shader(
        "../shaders/vertex_core.glsl",
        "../shaders/fragment_core.glsl"
    );

    //Render Loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f, 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}
