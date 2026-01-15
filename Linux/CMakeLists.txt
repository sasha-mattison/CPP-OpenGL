cmake_minimum_required(VERSION 3.20)
project(app LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/glad.cpp
)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/dependencies/include  # stb, glad, etc
    ${PROJECT_SOURCE_DIR}/src                  # your own headers
    /usr/include                               # system includes (GLM usually here)
)

# Create executable
add_executable(${PROJECT_NAME} ${SRC})

# Find system libraries
find_package(OpenGL REQUIRED)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    glfw           # GLFW (installed via pacman or apt)
    ${OPENGL_gl_LIBRARY}  # OpenGL
    dl              # dynamic loader
    pthread         # threading (required by GLFW)
    X11             # X11 window system
    Xrandr          # X11 extension for resizing
    Xi              # X11 input
)
