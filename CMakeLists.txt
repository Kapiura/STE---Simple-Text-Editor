# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(STE)

# Add an executable target
add_executable(ste src/main.cpp)

# Link SDL library
find_package(SDL2 REQUIRED)
target_link_libraries(ste PRIVATE SDL2::SDL2)

# Include directories
target_include_directories(ste PRIVATE include)

