cmake_minimum_required(VERSION 3.20)
project(app LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/glad.cpp
    ${PROJECT_SOURCE_DIR}/shaders/*.cpp
    ${PROJECT_SOURCE_DIR}/mesh/*.cpp
    ${PROJECT_SOURCE_DIR}/window/*.cpp
)

include_directories(
    ${PROJECT_SOURCE_DIR}/dependencies/include
    ${PROJECT_SOURCE_DIR}/mesh
    ${PROJECT_SOURCE_DIR}/shaders
    ${PROJECT_SOURCE_DIR}/window
    ${PROJECT_SOURCE_DIR}/src
)

add_executable(${PROJECT_NAME} ${SRC})

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wno-deprecated)

find_package(OpenGL REQUIRED)

# Check OS
if(APPLE)
    include_directories(/opt/homebrew/include)
    
    target_link_libraries(${PROJECT_NAME}
        "${PROJECT_SOURCE_DIR}/dependencies/library/libglfw.3.4.dylib"
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
    )

elseif(UNIX AND NOT APPLE)
    include_directories(/usr/include)
    
    target_link_libraries(${PROJECT_NAME}
        glfw          
        ${OPENGL_gl_LIBRARY} 
        dl             
        pthread       
        X11          
        Xrandr       
        Xi     
    )
endif()