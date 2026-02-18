cmake_minimum_required(VERSION 3.20)
project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/glad.cpp
    ${PROJECT_SOURCE_DIR}/shaders/*.cpp
    ${PROJECT_SOURCE_DIR}/mesh/*.cpp
    ${PROJECT_SOURCE_DIR}/window/*.cpp
)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/dependencies/include
    ${PROJECT_SOURCE_DIR}/src
    /opt/homebrew/include
)

add_executable(${PROJECT_NAME} ${SRC})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    "${PROJECT_SOURCE_DIR}/dependencies/library/libglfw.3.4.dylib"
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework CoreFoundation"
)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wno-deprecated)
