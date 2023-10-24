# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(STE)

# Add an executable target
add_executable(ste src/main.cpp src/Editor.cpp)

# Add path to your SDL2 source directory
add_subdirectory(lib/SDL2)

# Link against the SDL2 library
target_link_libraries(ste PRIVATE SDL2)

# Add the header files to the project
target_sources(ste PRIVATE include/Editor.h)
