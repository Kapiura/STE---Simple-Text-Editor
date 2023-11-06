cmake_minimum_required(VERSION 3.5)

project(STE)

add_executable(ste src/main.cpp src/Editor.cpp)

add_subdirectory(lib/SDL2)

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)


target_sources(${PROJECT_NAME} PRIVATE include/Editor.h)
