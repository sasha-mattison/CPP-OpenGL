# Linux Versions are unmaintained (Temporarily)
# Arch Linux 
## Requirements 
- GLM 
- GLFW
- CMake
- OpenGL (mesa)
- C++ compiler (base-devel)

Install with: `sudo pacman -Syu base-devel mesa glfw-x11 glm libglvnd cmake`

## Installation Instructions
1. Clone the repository to whichever directory you please. `git clone git@github.com:sasha-mattison/CPP-OpenGL.git`
2. Install dependencies with the following command: `sudo pacman -Syu base-devel mesa glfw-x11 glm libglvnd cmake`
3. change directory into the project root.
4. change directory into Linux folder.
5. Remove the build folder and recreate to get rid of conflicting CMake builds: `rm -rf build` `mkdir build`
6. Configure your project with CMake.
