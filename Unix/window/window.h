#pragma once
#include <GLFW/glfw3.h>

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    void processInput();
    bool shouldClose() const;
    void swapBuffers() const;
    void pollEvents() const;
    GLFWwindow* get() const;

private:
    GLFWwindow* window = nullptr;

    int width, height;
    int windowedWidth, windowedHeight;
    int windowedX, windowedY;
    bool fullscreen = false;

    static void toggleFullscreenStatic(GLFWwindow* window);
    void toggleFullscreen();
};
