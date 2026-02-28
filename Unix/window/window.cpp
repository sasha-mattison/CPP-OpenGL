#include "window.h"
#include <iostream>

Window::Window(int w, int h, const char* title)
    : width(w), height(h),
      windowedWidth(w), windowedHeight(h),
      windowedX(100), windowedY(100) {

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        window = nullptr;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);
}

Window::~Window() {
    if (window)
        glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* Window::get() const {
    return window;
}

bool Window::shouldClose() const {
    return window && glfwWindowShouldClose(window);
}

void Window::swapBuffers() const {
    if (window)
        glfwSwapBuffers(window);
}

void Window::pollEvents() const {
    glfwPollEvents();
}

void Window::processInput() {
    if (!window) return;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    static bool fPressedLastFrame = false;
    bool fPressed = glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS;
    if (fPressed && !fPressedLastFrame) {
        toggleFullscreen();
    }
    fPressedLastFrame = fPressed;
}

void Window::toggleFullscreen() {
    fullscreen = !fullscreen;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    if (fullscreen) {
        glfwGetWindowPos(window, &windowedX, &windowedY);
        glfwGetWindowSize(window, &windowedWidth, &windowedHeight);

        glfwSetWindowMonitor(window, monitor,
                             0, 0,
                             mode->width, mode->height,
                             mode->refreshRate);
    } else {
        glfwSetWindowMonitor(window, nullptr,
                             windowedX, windowedY,
                             windowedWidth, windowedHeight,
                             0);
    }
}
