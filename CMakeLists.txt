cmake_minimum_required(VERSION 3.5.1)

project(ste)

# ---------------------------------------------------------------------------------
# Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
# https://github.com/aminosbh/sdl2-ttf-sample/blob/master/CMakeLists.txt
# Add SDL2 CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
# ---------------------------------------------------------------------------------

# Add all c source files under the src directory
file(GLOB SOURCES "src/*.cpp") # Add InputEditor.cpp
add_executable(${PROJECT_NAME} ${SOURCES})

# Add all headers files under the include directory
target_include_directories(${PROJECT_NAME} PRIVATE include)

# ---------------------------------------------------------------------------------
# Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
# https://github.com/aminosbh/sdl2-ttf-sample/blob/master/CMakeLists.txt
# Add compiler errors/warnings flags
target_compile_options(${PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX>)
target_compile_options(${PROJECT_NAME} PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -Werror>)
# ---------------------------------------------------------------------------------

# Add SDL2 library
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::Main)

# Add SDL2_ttf library
find_package(SDL2_ttf REQUIRED)
target_link_libraries(${PROJECT_NAME} SDL2::TTF)

# ---------------------------------------------------------------------------------
# Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
# https://github.com/aminosbh/sdl2-ttf-sample/blob/master/CMakeLists.txt
# Copy assets
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
# ---------------------------------------------------------------------------------

