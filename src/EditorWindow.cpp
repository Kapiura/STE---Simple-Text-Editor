#include "../include/EditorWindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <iostream>
#include <string>

EditorWindow::EditorWindow (std::string title, int height, int width)
    : _title (title), _file_name ("unnamed"), _height (height), _width (width)
{
  _path = std::filesystem::current_path ();
  std::cout << "EditorWindow object has been created\n";
  std::string temp = _title + " - " + _file_name;
  _window = SDL_CreateWindow (temp.c_str (), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, _width, _height,
                              SDL_WINDOW_RESIZABLE);
  _renderer = SDL_CreateRenderer (_window, -1, SDL_RENDERER_SOFTWARE);
  if (!_window)
    {
      std::cout << "SDL error while creating window: " << SDL_GetError ()
                << "\n";
    }
  if (!_renderer)
    {
      std::cout << "SDL error while creating surface: " << SDL_GetError ()
                << "\n";
    }
  SDL_SetWindowMinimumSize (_window, 150, 100);
}

EditorWindow::~EditorWindow ()
{
  SDL_DestroyRenderer (_renderer);
  SDL_DestroyWindow (_window);
  std::cout << "EditorWindow object has been destroyed\n";
}

void
EditorWindow::render ()
{
  SDL_RenderClear (_renderer);
}

int
EditorWindow::getWindowWidth () const
{
  int width, height;
  SDL_GetWindowSize (_window, &width, &height);
  return width;
}

int
EditorWindow::getWindowHeight () const
{
  int width, height;
  SDL_GetWindowSize (_window, &width, &height);
  return height;
}

SDL_Renderer *
EditorWindow::getRenderer () const
{
  return _renderer;
}

SDL_Window *
EditorWindow::getWindow () const
{
  return _window;
}
TTF_Font *
EditorWindow::getFont () const
{
  return _font;
}
